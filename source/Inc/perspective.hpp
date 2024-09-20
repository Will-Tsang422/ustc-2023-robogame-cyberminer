#pragma once
#ifndef PERSPECTIVE_HPP
#define PERSPECTIVE_HPP
#include <opencv2/opencv.hpp>
#include <ctime>
using namespace std;
using namespace cv;

/**
 * @brief 将图像进行透视变换，使矩形位于图像中央
 *
 *
 *
 * @param img 输入图像; rect 矩形
 * @return dst_img 变换后的图像
 */
Mat transform(Mat, Rect);

#endif