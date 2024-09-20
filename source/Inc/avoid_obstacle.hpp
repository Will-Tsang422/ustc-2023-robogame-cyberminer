#pragma once
#ifndef AVIOD_OBSTACLE_HPP
#define AVOID_OBSTACLE_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <ctime>
using namespace std;
using namespace cv;

Mat temp = imread("/home/cyberminer/robogame/pictures/obstacle.png");
/**
 * @brief 利用模板匹配得到障碍物轮廓并绘制
 *
 *
 *
 * @param img 输入图像
 * @return
 */
void detect_obstacle(Mat &);

void findcontours(Mat &, vector<vector<Point>> &);

int Humoment_detect(Mat);

#endif