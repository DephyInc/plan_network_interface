#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networkinterface.h"
#include <iostream>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    , tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":icons/d_logo_small_outlined.png"));

    this->setWindowTitle("Network Command Sender");

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::sendStreamOn);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::sendStreamOff);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::sendExoPowerOn);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::sendExoPowerOff);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::connectToPlanGUI);
}

void MainWindow::connectToPlanGUI()
{
    hostAddress = ui->textEdit->toPlainText();
    tcpSocket->disconnectFromHost();

    connect(tcpSocket, &QTcpSocket::channelReadyRead, this, &MainWindow::readSocket, Qt::UniqueConnection);

    tcpSocket->connectToHost(hostAddress, SERVER_TCP_PORT);

    bool b = tcpSocket->isOpen();

    if(b)
    {
        out.setDevice(tcpSocket);
        out.setVersion(QDataStream::Qt_5_10);
    }
    else
    {
        ui->label->setText("Could not connect");
        std::cout << "Could not connect" << std::endl;
    }

}

void MainWindow::readSocket()
{
    QByteArray response = tcpSocket->readAll();
    for(int i = 0; i < response.size(); i++)
    {
        if(response.at(i) == CONNECTION_ACK)
        {
            QString l = QStringLiteral("Connected to ") + hostAddress;
            ui->label->setText(l);
            std::cout << l.toStdString() << std::endl;
        }
    }

}

void MainWindow::sendCommand(char cmd, char param)
{
    if(!tcpSocket->isOpen()) return;
    bytes[0] = cmd;
    bytes[1] = param;
    tcpSocket->write(bytes, COMMAND_LENGTH);
}

void MainWindow::sendStreamOn()
{
    if(!tcpSocket->isOpen()) return;
    sendCommand(EXO_STREAM_CMD, STREAM_START);
    std::cout << "Sent stream on \n";
    fflush(stdout);
}

void MainWindow::sendStreamOff()
{
    if(!tcpSocket->isOpen()) return;
    sendCommand(EXO_STREAM_CMD, STREAM_STOP);
    std::cout << "Sent stream off \n";
    fflush(stdout);
}

void MainWindow::sendExoPowerOn()
{
    if(!tcpSocket->isOpen()) return;
    sendCommand(EXO_POWER_CMD, POWER_HIGH);
    std::cout << "Sent power high \n";
    fflush(stdout);
}

void MainWindow::sendExoPowerOff()
{
    if(!tcpSocket->isOpen()) return;
    sendCommand(EXO_POWER_CMD, POWER_LOW);
    std::cout << "Sent power low \n";
    fflush(stdout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
