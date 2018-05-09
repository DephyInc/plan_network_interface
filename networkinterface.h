#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

const char EXO_POWER_CMD  = 0x4C;
const char EXO_STREAM_CMD = 0x93;

const char POWER_HIGH = 0x7E;
const char POWER_LOW = 0x81;

const char STREAM_START = 0x3A;
const char STREAM_STOP = 0x83;

const char COMMAND_LENGTH = 2;

const int SERVER_TCP_PORT = 63367;

const char CONNECTION_ACK = 0x44;

#endif // NETWORKINTERFACE_H
