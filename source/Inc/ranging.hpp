#include <wiringPi.h>
#include <wiringSerial.h>
const double standard_distance = 35.0;
const double safe_distance = 8.0;
class HC_SR04
{
private:
    int trig, echo;
    const int timeout = 1000000;
    const int maxtime = 200000;

public:
    HC_SR04(int trig, int echo);
    unsigned int pulseIn(int, int);
    double get_distance();
};