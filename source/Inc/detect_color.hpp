#pragma once
#ifndef DETECT_COLOR_H
#define DETECT_COLOR_H
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace cv;

const int MIN_AREA = 6000;
enum COLOR
{
    BLUE,
    ORANGE,
    PURPLE
};
struct Ore
{
    COLOR color;
    Rect rect;
    Ore(const COLOR &color, const Rect &rect)
        : color(color), rect(rect)
    {
    }
    Ore() = default;
    bool operator<(const Ore &ore) const
    {
        return rect.x < ore.rect.x;
    }
};
//9.24 16:45
const Scalar blue_low(100, 50, 50);
const Scalar blue_high(150, 255, 255);
//9.24 16:47
const Scalar orange_low(0, 50, 50);
const Scalar orange_high(50, 255, 255);

// const Scalar orange_low(0, 160, 150);
// const Scalar orange_high(50, 255, 255);
// const Scalar purple_low(100, 40, 140);
// const Scalar purple_high(220, 120, 200);
//9.24 15：01
// const Scalar purple_low(140, 50, 50);
// const Scalar purple_high(230, 255, 255);

const Scalar purple_low(160, 0, 100);
const Scalar purple_high(255, 255, 255);


const vector<Scalar> color_low = {blue_low, orange_low, purple_low};
const vector<Scalar> color_high = {blue_high, orange_high, purple_high};

const string ore[3] = {"Blue", "Orange", "Purple"};
const string ore_CN[3] = {"蓝色", "橙色", "紫色"};

/**
 * @brief 寻找指定颜色的矿石
 *
 *
 *
 * @param 输入图像img，指定颜色color
 * @return 返回矿石的矩形框
 */
vector<Rect> find_color(Mat, COLOR);
/**
 * @brief 寻找特定颜色的矿石（Debug）
 *
 *
 *
 * @param 输入图像img，指定颜色color
 * @return 返回矿石的矩形框
 */
vector<Rect> find_one_color(Mat);
/**
 * @brief 寻找指定颜色的矿石
 *
 *
 *
 * @param 输入图像img，指定颜色color
 * @return 返回矿石的旋转矩形框
 */
vector<RotatedRect> find_color_rotated(Mat, COLOR);
/**
 * @brief 绘制旋转矩形框
 *
 *
 *
 * @param 输入图像img，旋转矩形rect
 * @return
 */
void draw_rotatedrect(Mat &, RotatedRect);

bool detect_color(Mat, COLOR);

bool sort_ores(Mat, uint8_t *);

int sort_fuels(Mat, uint8_t *);

/**
 * @brief 添加文本
 *
 *
 *
 * @param 输入图像img，指定颜色color，绘制点point
 * @return
 */
void add_text(Mat &, COLOR, Point2f);

#endif