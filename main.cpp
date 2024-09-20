#include "source/Inc/detect_color.hpp"
#include "source/Inc/distance.hpp"
#include "source/Inc/white_balance.hpp"
#include "source/Inc/ranging.hpp"
#include "source/Inc/serial_connect.hpp"
#include "source/Inc/take_picture.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>


void switch_statu(uint8_t readbuf[])
{
    if (readbuf[0] == check_ores && readbuf[1] == check_ores)
    {
        statu = check_ores;
        cout << "start checking ores" << endl;
    }
    else if (readbuf[0] == check_fuels && readbuf[1] == check_fuels)
    {
        statu = check_fuels;
        cout << "Start checking fuels" << endl;
    }
    else if (readbuf[0] == check_aerolites && readbuf[1] == check_aerolites)
    {
        statu = check_aerolites;
        cout << "Start checking aerolites" << endl;
    }
    else if (readbuf[0] == over && readbuf[1] == over)
    {
        statu = check_aerolites;
        cout << "Victory!" << endl;
    }
    else
    {
        statu = waiting;
        cout << "writebuf:" << readbuf[0] << ' ' << readbuf[1] << endl;
        cout << "Still waiting" << endl;
    }
}

int main(int argc, char *argv[])
{

    wiringPiSetup();
    int fd = serialOpen("/dev/ttyAMA1", 115200);
    pid_t pid = fork();
    if (pid < 0)
    {
        cout << "F\033[41mork Failed!\033[0m" << endl;
    }
    else if (pid == 0)
    {
        while (true)
        {
            if (!executing)
            {
                uint8_t readbuf[2];
                int readbytes = serialRead(fd, readbuf);
                if (readbytes)
                {
                    switch_statu(readbuf);
                }
            }
            delay(1000);
        }
    }
    else
    {
        while (true)
        {
            switch (statu)
            {
            case check_ores:
            {
                cout << "checking ores" << endl;
                executing = true;
                Mat img;
                string name = "pictures/ores.jpg";
                uint8_t writebuf[7];
                bool finished;
                do
                {
                    take_picture(name);
                    img = imread(name);
                    finished = sort_ores(img, writebuf);
                } while (finished == false);
                serialWrite(fd, writebuf, 7);
                executing = false;
                break;
            }
            case check_fuels:
            {
                cout << "checking fuels" << endl;
                executing = true;
                Mat img;
                string name = "pictures/fuels.jpg";
                uint8_t writebuf[5];
                bool finished;
                do
                {
                    take_picture(name);
                    img = imread(name);
                    finished = sort_fuels(img, writebuf);
                } while (finished == false);
                serialWrite(fd, writebuf, 5);
                executing = false;
                break;
            }
            case check_aerolites:
            {
                executing = true;
                HC_SR04 my_HC_SR04(0, 7);
                uint8_t writebuf[4];
                writebuf[0] = writebuf[3] = 0xFF;
                double distance;
                do
                {
                    distance = my_HC_SR04.get_distance();
                } while (distance == 0);
                writebuf[1] = (uint8_t)round(distance);
                writebuf[2] = (uint8_t)(distance > standard_distance);
                serialWrite(fd, writebuf, 4);
                executing = false;
                break;
            }
            case over:
                goto STOP;
            default:
                break;
            }
        }
    }
STOP:
    kill(pid, SIGTERM);
    serialClose(fd);
    return 0;
}
