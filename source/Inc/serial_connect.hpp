#pragma once
#ifndef SERIAL_CONNECT_HPP
#define SERIAL_CONNECT_HPP
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>
// #include <termios.h>
// #include <unistd.h>
using namespace std;

/**
 * @brief 将信号写入串口
 *
 *
 *
 * @param 端口号，写入字节数，将发送的数组
 * @return
*/
int serialWrite(int, uint8_t *, int);
/**
 * @brief 读取串口中的信号
 *
 *
 *
 * @param 端口号，接收数组
 * @return
*/
int serialRead(int, uint8_t *);

#endif