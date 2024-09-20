#include "../Inc/serial_connect.hpp"
#include "serial_connect.hpp"

int serialWrite(int fd, uint8_t writebuf[], int length)
{
    int bytesWrite = 0;
    while (bytesWrite < length)
    {
        serialPutchar(fd, writebuf[bytesWrite]);
        bytesWrite++;
    }
    return bytesWrite;
}

int serialRead(int fd, uint8_t readbuf[])
{
    int bytesRead = 0;
    uint8_t byte;
    int count = serialDataAvail(fd);
    while (bytesRead < count)
    {
        byte = serialGetchar(fd);
        readbuf[bytesRead] = byte;
        bytesRead++;
    }
    return bytesRead;
}
