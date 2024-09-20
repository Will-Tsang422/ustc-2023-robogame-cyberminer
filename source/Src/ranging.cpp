#include "../Inc/ranging.hpp"

HC_SR04::HC_SR04(int trig, int echo) : trig(trig), echo(echo)
{
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

unsigned int HC_SR04::pulseIn(int pin, int state)
{
    unsigned int pulseWidth = 0;
    unsigned int startMicros, endMicros;
    startMicros = micros();
    // 等待引脚状态变为state或超时
    while (digitalRead(pin) != state)
        if (micros() - startMicros > timeout)
            return -1;
    // 记录引脚变为state的时刻
    startMicros = micros();
    // 等待引脚状态变为!state或超时
    while (digitalRead(pin) == state)
        if (micros() - startMicros > timeout)
            return -2;
    // 记录引脚变为!state的时刻
    endMicros = micros();
    // 计算脉冲宽度
    pulseWidth = endMicros - startMicros;
    // 超出设定最远距离则返回0
    // return pulseWidth < maxtime ? pulseWidth : maxtime;
    return pulseWidth;
}

double HC_SR04::get_distance()
{
    digitalWrite(trig, LOW);
    delayMicroseconds(5);
    digitalWrite(trig, HIGH);
    delayMicroseconds(20);
    digitalWrite(trig, LOW);
    double distance = pulseIn(echo, HIGH) / 58.0;
    return distance;
}