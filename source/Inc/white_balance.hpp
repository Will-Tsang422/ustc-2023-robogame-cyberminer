#pragma once
#ifndef WHITE_BALANCE_HPP
#define WHITE_BALANCE_HPP
#include <opencv2/opencv.hpp>
#include <vector>
#include <chrono>
using namespace std;
using namespace cv;

void equalize_YCrCb(Mat &);

void equalize_HSV(Mat &);
/**
 * @brief 直接对原图像使用均值白平衡算法
 *
 *
 *
 * @param img 初始图像
 * @return
 */
void mean_white_balance(Mat &);

/**
 * @brief 对原图像使用完美白平衡算法
 *
 *
 *
 * @param src 初始图像
 * @return dst 白平衡图像
 */
Mat perfect_white_balance(Mat);

#endif