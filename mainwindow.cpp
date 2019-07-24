#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networkinterface.h"
#include <iostream>
#include "w_event.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
	, tcpSocket(new QTcpSocket(this))
{
	ui->setupUi(this);
	setWindowIcon(QIcon(":icons/d_logo_small_outlined.png"));

	this->setWindowTitle("Network Command Sender");

	/*
	//Open Event Flag window
	evWindow = new QWidget();
	evWindow->resize(286, 272);
	evWindow->setWindowTitle("Event Flag");
	evWindow->show();
	W_Event *myEventWin = new W_Event(evWindow);
	myEventWin->show();
	*/

	//Default text:
	ui->textEdit->setText("127.0.0.1");

	connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::sendStreamOn);
	connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::sendStreamOff);
	connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::sendExoPowerOn);
	connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::sendExoPowerOff);
	connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::connectToPlanGUI);
	connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::requestTimestamps);
	connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::sendExoResetStats);
	connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::sendExoStartLearning);
	connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::sendExoStopLearning);
	connect(ui->pushButton_10, &QPushButton::clicked, this, &MainWindow::sendExoReadUTT);
	connect(ui->pushButton_11, &QPushButton::clicked, this, &MainWindow::sendTimestamp);
	connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::sendGaussianArray1);
	connect(ui->pushButton_13, &QPushButton::clicked, this, &MainWindow::sendGaussianArray2);

	//connect(myEventWin, &W_Event::buttonClick, this, &MainWindow::eventFlag);
}

void MainWindow::eventFlag(int index)
{
	int8_t v = (int8_t) W_Event::getEventCode();
	sendEventFlag(v);
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

	if(response.at(0) == CONNECTION_ACK)
	{
		QString l = QStringLiteral("Connected to ") + hostAddress;
		ui->label->setText(l);
		std::cout << l.toStdString() << std::endl;
	}
	else
	{
		ui->label->setText(response);
		std::cout << response.toStdString() << std::endl;
	}
}

void MainWindow::sendCommand(char cmd, char param)
{
	if(!tcpSocket->isOpen()) return;
	bytes[0] = cmd;
	bytes[1] = param;
	tcpSocket->write(bytes, COMMAND_LENGTH);
}

void MainWindow::sendLongCommand(char cmd, char param, char *payload, char numb)
{
	if(!tcpSocket->isOpen()) return;
	longBytes[0] = cmd;
	longBytes[1] = param;
	for(int i = 0; i < numb; i++)
	{
		longBytes[2+i] = payload[i];
	}
	tcpSocket->write(longBytes, COMMAND_LENGTH_GAUSSIAN);
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

void MainWindow::sendExoResetStats()
{
	if(!tcpSocket->isOpen()) return;
	sendCommand(EXO_CUSTOM_CMD, CU_RESET_STATS);
	std::cout << "Sent Reset Stats \n";
	fflush(stdout);
}

void MainWindow::sendExoStartLearning()
{
	if(!tcpSocket->isOpen()) return;
	sendCommand(EXO_CUSTOM_CMD, CU_START_LEARNING);
	std::cout << "Sent Exo Start Learning\n";
	fflush(stdout);
}

void MainWindow::sendExoStopLearning()
{
	if(!tcpSocket->isOpen()) return;
	sendCommand(EXO_CUSTOM_CMD, CU_STOP_LEARNING);
	std::cout << "Sent Exo Stop Learning\n";
	fflush(stdout);
}

void MainWindow::sendExoPowerOn()
{
	if(!tcpSocket->isOpen()) return;
	sendCommand(EXO_POWER_CMD, POWER_HIGH);
	std::cout << "Sent power high\n";
	fflush(stdout);
}

void MainWindow::sendExoPowerOff()
{
	if(!tcpSocket->isOpen()) return;
	sendCommand(EXO_POWER_CMD, POWER_LOW);
	std::cout << "Sent power low\n";
	fflush(stdout);
}

void MainWindow::sendExoReadUTT()
{
	if(!tcpSocket->isOpen()) return;
	sendCommand(EXO_CUSTOM_CMD, CU_READ_UTT);
	std::cout << "Sent Read UTT\n";
	fflush(stdout);
}

void MainWindow::requestTimestamps()
{
	if(!tcpSocket->isOpen()) return;
	sendCommand(EXO_TIMESTAMP_CMD, 0);
	std::cout << "Sent timestamp request\n";
	fflush(stdout);
}

void MainWindow::sendTimestamp()
{
	if(!tcpSocket->isOpen()) return;
	sendCommand(EXO_TIMESTAMP_CMD, 1);
	std::cout << "Wrote timestamp\n";
	fflush(stdout);
}

void MainWindow::gaussianToBytes(int16_t ga[GA_ROWS][GA_COLS], char *bArray)
{
	int b = 0;
	for(int r = 0; r < GA_ROWS; r++)
	{
		for(int c = 0; c < GA_COLS; c++)
		{
			 bArray[b++] = (uint8_t)((ga[r][c] >> 8) & 0xFF);
			 bArray[b++] = (uint8_t)(ga[r][c] & 0xFF);
		}
	}
}

void MainWindow::sendGaussianArray1()
{
	if(!tcpSocket->isOpen()) return;

	char testArray[30];
	gaussianToBytes(gaArr1, testArray);
	sendLongCommand(EXO_GAUSSIAN_CMD, 1, testArray, 30);

	std::cout << "Wrote Gaussians #1\n";
	fflush(stdout);
}

void MainWindow::sendGaussianArray2()
{
	if(!tcpSocket->isOpen()) return;

	char testArray[30];
	gaussianToBytes(gaArr2, testArray);
	sendLongCommand(EXO_GAUSSIAN_CMD, 1, testArray, 30);

	std::cout << "Wrote Gaussians #2\n";
	fflush(stdout);
}

void MainWindow::sendEventFlag(int8_t f)
{
	if(!tcpSocket->isOpen()) return;
	sendCommand(EXO_EVENT_CMD, f);
	std::cout << "Sent stream on \n";
	fflush(stdout);
}

MainWindow::~MainWindow()
{
	evWindow->close();
	delete ui;
	delete evWindow;
}
