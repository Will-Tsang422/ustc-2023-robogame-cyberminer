#include "source/Inc/ranging.hpp"
#include <iostream>

int main()
{
    wiringPiSetup();
    HC_SR04 my_HC_SR04(6, 5);
    double distance;
    while (true)
    {
        distance = my_HC_SR04.get_distance();
        std::cout << distance << "cm" << std::endl;
        delay(1000);
    }
    return 0;
}