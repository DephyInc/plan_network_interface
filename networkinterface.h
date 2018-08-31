#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

//Commands:
const char EXO_STREAM_CMD = 0x01;
const char EXO_POWER_CMD  = 0x02;
const char EXO_TIMESTAMP_CMD = 0x03;
const char EXO_EVENT_CMD = 0x04;

//Parameters:
const char STREAM_START = 0x11;
const char STREAM_STOP = 0x12;
const char POWER_HIGH = 0x13;
const char POWER_LOW = 0x14;

//Settings & internal:
const char COMMAND_LENGTH = 3;
const int SERVER_TCP_PORT = 63367;
const char CONNECTION_ACK = 0x7F;
const char OK_RESPONSE[4] = "AOK";
const char ERR_RESPONSE[4] = "ERR";

#endif // NETWORKINTERFACE_H
