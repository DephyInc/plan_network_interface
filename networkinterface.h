#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

//Gaussians:
#define GA_COLS				3
#define GA_ROWS				5
#define GA_MEAN				0
#define GA_SIGMA			1
#define GA_AMPLITUDE		2

//Commands:
const char EXO_STREAM_CMD = 0x01;
const char EXO_POWER_CMD  = 0x02;
const char EXO_TIMESTAMP_CMD = 0x03;
const char EXO_EVENT_CMD = 0x04;
const char EXO_CUSTOM_CMD = 0x05;
const char EXO_GAUSSIAN_CMD = 0x06;

//Parameters:
const char STREAM_START = 0x11;
const char STREAM_STOP = 0x12;
const char POWER_HIGH = 0x13;
const char POWER_LOW = 0x14;
const char CU_RESET_STATS = 0x15;
const char CU_START_LEARNING = 0x16;
const char CU_STOP_LEARNING = 0x17;
const char CU_READ_UTT = 0x18;

//Settings & internal:
const char COMMAND_LENGTH = 3;	//Default
const int SERVER_TCP_PORT = 63367;
const char CONNECTION_ACK = 0x7F;
const char OK_RESPONSE[4] = "AOK";
const char ERR_RESPONSE[4] = "ERR";

#endif // NETWORKINTERFACE_H
