#pragma once
#ifndef DISTANCE_H
#define DISTANCE_H
#include <opencv2/opencv.hpp>
#include <chrono>
using namespace std;
using namespace cv;

constexpr auto HALF_LENGTH = 50; // 矿石的真实尺寸的一半，单位为mm;

const vector<Point3f> ore_vertices{
	Point3f(-HALF_LENGTH, -HALF_LENGTH, 0),
	Point3f(HALF_LENGTH, -HALF_LENGTH, 0),
	Point3f(HALF_LENGTH, HALF_LENGTH, 0),
	Point3f(-HALF_LENGTH, HALF_LENGTH, 0)}; // 矿石正面的四个顶点的坐标，单位为mm

// 相机标定参数
const Mat cameraMatrix = (Mat_<double>(3, 3) << 461.155, 0, 294.486, 0, 462.527, 256.353, 0, 0, 1); // 相机内参矩阵
// const Mat My_distCoeffs = (Mat_<double>(1, 5) << -0.09622, 0.59863, -0.00419, 0.00118, -0.89230);  //相机畸变系数
const Mat zeros = Mat::zeros(1, 5, CV_32FC1); // 无畸变

/**
 * @brief 计算相机相对矿石中心的位置
 *
 *
 *
 * @param rect 矿石的矩形框
 * @return Mat 相机相对矿石中心的位置
 */
Mat measure_distance(Rect);

Mat measure_distance_rotated(RotatedRect);
#endif