#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include <mutex>
using namespace std;
const int milliseconds = 10000;
mutex mux;
// piBoardRev() == 2
void serialWrite(int fd, uint8_t writebuf[], int length)
{
    for (int i = 0; i < length; i++)
    {
        serialPutchar(fd, writebuf[i]);
    }
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

void continueRead(int fd)
{
    uint8_t byte;
    while (true)
    {
        int count = serialDataAvail(fd);
        while (count)
        {
            byte = serialGetchar(fd);
            cout << byte;
            count--;
            if (count == 0)
                cout << endl;
        }
    }
    return;
}

int multiprocess()
{
    wiringPiSetup();
    int fd = serialOpen("/dev/ttyAMA1", 115200);
    uint8_t readbuf[8];
    uint8_t writebuf[] = {1, 2, 3, 4};
    int count, readbytes;
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed!\n");
    }
    else if (pid == 0)
    {
        while (true)
        {
            readbytes = serialRead(fd, readbuf);
            for (int i = 0; i < readbytes; i++)
            {
                cout << readbuf[i];
                if (i == readbytes - 1)
                    cout << endl;
            }
        }
    }
    else
    {
        while (true)
        {

            serialWrite(fd, writebuf, 4);
            for (int i = 0; i < 4; i++)
            {
                writebuf[i] += 1;
            }
            delay(milliseconds);
        }
    }
    serialClose(fd);
    return 0;
}

int multithread()
{
    int fd = serialOpen("/dev/ttyAMA1", 115200);
    uint8_t readbuf[8];
    uint8_t writebuf[] = {1, 2, 3, 4};
    int count, readbytes;
    while (true)
    {
        thread t(continueRead, fd);
        t.detach();
        serialWrite(fd, writebuf, 4);
        delay(milliseconds);
    }
    serialClose(fd);
    return 0;
}

int shared_data = 0;
void add(int n)
{
    for (int i = 0; i < 100000; i++)
    {
        lock_guard<mutex> lg(mux);
        shared_data++;
        cout << "thread " << n << endl;
    }
}

void sub()
{
    for (int i = 0; i < 10000; i++)
    {
        shared_data--;
    }
}

int main()
{
    thread t1(add, 1), t2(add, 2);
    t1.join();
    t2.join();
    cout << shared_data << endl;
    return 0;
}
