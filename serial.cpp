#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

using namespace std;

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

int main()
{
    wiringPiSetup();
    int fd = serialOpen("/dev/ttyAMA1", 115200);
    uint8_t writebuf[] = {0x1, 0x2, 0x3, 0x4};
    uint8_t readbuf[8];
    int count, readbytes;
    while (true)
    {
        readbytes = serialRead(fd, readbuf);
        for (int i = 0; i < readbytes; i++)
        {
            cout << readbuf[i];
            if (i == readbytes - 1)
                cout << endl;
        }
        serialWrite(fd, writebuf, 4);
        delay(1000);
    }
    serialClose(fd);
    return 0;
}