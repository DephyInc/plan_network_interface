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
	void sendGaussianArray1();
	void sendGaussianArray2();
	void gaussianToBytes(int16_t ga[GA_ROWS][GA_COLS], char *bArray);

private:
	Ui::MainWindow *ui;
	QWidget *evWindow;

	QDataStream out;
	QTcpSocket *tcpSocket;
	QNetworkSession *ns;
	QString hostAddress;
	char bytes[COMMAND_LENGTH];
	char longBytes[100];

	int16_t gaArr1[GA_ROWS][GA_COLS] = {{200, 100, 500},\
										 {300, 75, 650},\
										 {400, 50, 925},\
										 {500, 45, 1500},\
										 {600, 45, 2250}};

	int16_t gaArr2[GA_ROWS][GA_COLS] = {{201, 101, 501},\
										 {301, 76, 651},\
										 {401, 51, 926},\
										 {501, 46, 1501},\
										 {601, 46, 2251}};
};

#endif // MAINWINDOW_H
