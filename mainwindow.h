#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QNetworkSession>

#include "networkinterface.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void sendCommand(char cmd, char param);
	void sendLongCommand(char cmd, char param, char *payload, char numb);

public slots:
	void readSocket();
	void connectToPlanGUI();
	void sendStreamOn();
	void sendStreamOff();
	void sendExoPowerOn();
	void sendExoPowerOff();
	void requestTimestamps();
	void sendTimestamp();
	void eventFlag(int index);
	void sendEventFlag(int8_t f);
	void sendExoResetStats();
	void sendExoStartLearning();
	void sendExoStopLearning();
	void sendExoReadUTT();

private slots:
	void on_pbStartTrial_pressed();
	void on_pbRestartLearning_pressed();
	void on_pbEndTrial_pressed();

private:
	Ui::MainWindow *ui;
	QWidget *evWindow;

	QDataStream out;
	QTcpSocket *tcpSocket;
	QNetworkSession *ns;
	QString hostAddress;
	char bytes[COMMAND_LENGTH];
	char longBytes[100];
};

#endif // MAINWINDOW_H
