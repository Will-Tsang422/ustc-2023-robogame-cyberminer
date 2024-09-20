#include "source/Inc/detect_color.hpp"
#include "source/Inc/distance.hpp"
#include "source/Inc/white_balance.hpp"
#include "source/Inc/ranging.hpp"
#include "source/Inc/serial_connect.hpp"
#include "source/Inc/take_picture.hpp"
#include <sys/types.h>
#include <unistd.h>

const uint8_t waiting = 0x00;
const uint8_t over = 0xFF;
const uint8_t check_ores = 1;
const uint8_t check_fuels = 2;
const uint8_t check_aerolites = 3;
const uint8_t check_aerolites_c = 4;
uint8_t statu;

void switch_statu(uint8_t readbuf[])
{
    if (readbuf[0] == check_ores)
    {
        statu = check_ores;
        cout << "检测矿石中" << endl;
    }
    else if (readbuf[0] == check_fuels)
    {
        statu = check_fuels;
        cout << "检测燃料中" << endl;
    }
    else if (readbuf[0] == check_aerolites)
    {
        statu = check_aerolites;
        cout << "检测陨石中" << endl;
    }
    else if (readbuf[0] == check_aerolites_c)
    {
        statu = check_aerolites_c;
        cout << "持续检测陨石中" << endl;
    }
    else if (readbuf[0] == over)
    {
        statu = over;
        cout << "Victory!" << endl;
    }
    else
    {
        statu = waiting;
        cout << "等待中" << endl;
    }
}

int main(int argc, char *argv[])
{
    wiringPiSetup();
    int fd = serialOpen("/dev/ttyAMA1", 115200);
    serialFlush(fd);
    VideoCapture video(0);
    if (!video.isOpened())
    {
        cout << "\033[41m摄像头打开失败！\033[0m" << endl;
        return -1;
    }
    HC_SR04 HC_SR04_1(0, 7);
    HC_SR04 HC_SR04_2(6, 5);
    Mat img;
    while (true)
    {
        statu = waiting;
        uint8_t readbuf[1];
        int readbytes = serialRead(fd, readbuf);
        if (readbytes)
        {
            switch_statu(readbuf);
        }
        for (int i = 0; i < 10; i++)
        {
            video >> img;
            delay(5);
        }
        switch (statu)
        {
        case check_ores:
        {
            uint8_t writebuf[1] = {0};
            video.read(img);
            mean_white_balance(img);
            Rect like(img.cols / 3, img.rows / 3, img.cols / 3, img.rows / 3);
            img = img(like);
            imwrite("/home/cyberminer/robogame/pictures/ore.jpg", img);
            int is_orange = detect_color(img, ORANGE);
            int is_blue = detect_color(img, BLUE);
            if (is_orange)
            {
                if (is_blue)
                {
                    writebuf[0] = 1;
                }
                else
                {
                    writebuf[0] = 2;
                }
            }
            else
            {
                // if (is_blue)
                // {
                //     writebuf[0] = 1;
                // }
                // else
                // {
                //     writebuf[0] = 1;
                // }
                writebuf[0] = 1;
            }
            int writebytes = serialWrite(fd, writebuf, 1);
            if (writebytes == 1)
            {
                cout << "检测到" << ore_CN[writebuf[0] - 1] << "矿石" << endl;
            }
            break;
        }
        case check_fuels:
        {
            uint8_t writebuf[3] = {0};
            video >> img;
            Rect like(0, 2 * img.rows / 5, img.cols, img.rows / 2);
            img = img(like);
            mean_white_balance(img);
            imwrite("/home/cyberminer/robogame/pictures/fuel.jpg", img);
            bool is_purple = detect_color(img, PURPLE);
            int success = sort_fuels(img, writebuf);
            if (success > 0)
            {
                serialWrite(fd, writebuf, 3);
                cout << "燃料检测成功:" << success << endl;
                printf("%d %d %d\n", writebuf[0], writebuf[1], writebuf[2]);
            }
            else
            {
                cout << "燃料检测错误:" << success << endl;
            }
            break;
        }
        case check_aerolites:
        {
            uint8_t writebuf[1];
            double distance1, distance2, distance;
            distance1 = HC_SR04_1.get_distance();
            distance2 = HC_SR04_2.get_distance();
            distance = min(distance1, distance2);
            cout << "距离1：" << distance1 << " 距离2：" << distance2 << " 距离：" << distance << endl;
            writebuf[0] = 7 + (uint8_t)(distance > standard_distance);
            int writebytes = serialWrite(fd, writebuf, 1);
            break;
        }
        case check_aerolites_c:
        {
            uint8_t writebuf[1] = {7};
            double distance;
            do
            {
                distance = HC_SR04_1.get_distance();
                cout << "距离：" << distance << endl;
                serialWrite(fd, writebuf, 1);
            } while (distance > safe_distance);
            cout << "距离：" << distance << endl;
            writebuf[0] = 8;
            serialWrite(fd, writebuf, 1);
            break;
        }
        case over:
            goto STOP;
        default:
            break;
        }
    }
STOP:
    serialClose(fd);
    return 0;
}
