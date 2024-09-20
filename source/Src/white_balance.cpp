#include "../Inc/white_balance.hpp"

// void equalize_YCrCb(Mat &img)
// {
// 	auto begin = chrono::high_resolution_clock::now();
// 	Mat YCrCb;
// 	cvtColor(img, YCrCb, COLOR_BGR2YCrCb);
// 	vector<Mat> channels;
// 	split(YCrCb, channels);
// 	equalizeHist(channels[0], channels[0]);
// 	merge(channels, YCrCb);
// 	cvtColor(YCrCb, img, COLOR_YCrCb2BGR);
// 	auto end = chrono::high_resolution_clock::now();
// 	auto gap = chrono::duration_cast<chrono::milliseconds>(end - begin);
// 	cout << __func__ << " cost: " << gap.count() << endl;
// }

void equalize_HSV(Mat &img)
{
	Mat HSV;
	cvtColor(img, HSV, COLOR_BGR2HSV);
	vector<Mat> channels;
	split(HSV, channels);
	equalizeHist(channels[2], channels[2]);
	merge(channels, HSV);
	cvtColor(HSV, img, COLOR_HSV2BGR);
}

void mean_white_balance(Mat &img)
{
	vector<Mat> RGB;
	split(img, RGB);
	double r, g, b;
	b = mean(RGB[0])[0];
	g = mean(RGB[1])[0];
	r = mean(RGB[2])[0];
	double kr, kg, kb;
	kb = (r + g + b) / (3 * b);
	kg = (r + g + b) / (3 * g);
	kr = (r + g + b) / (3 * r);
	RGB[0] *= kb;
	RGB[1] *= kg;
	RGB[2] *= kr;
	merge(RGB, img);
}

// Mat perfect_white_balance(Mat src)
// {
// 	int row = src.rows;
// 	int col = src.cols;
// 	Mat dst(row, col, CV_8UC3);
// 	int HistRGB[767] = {0};
// 	int MaxVal = 0;
// 	for (int i = 0; i < row; i++)
// 	{
// 		for (int j = 0; j < col; j++)
// 		{
// 			MaxVal = max(MaxVal, (int)src.at<Vec3b>(i, j)[0]);
// 			MaxVal = max(MaxVal, (int)src.at<Vec3b>(i, j)[1]);
// 			MaxVal = max(MaxVal, (int)src.at<Vec3b>(i, j)[2]);
// 			int sum = src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i, j)[2];
// 			HistRGB[sum]++;
// 		}
// 	}
// 	int Threshold = 0;
// 	int sum = 0;
// 	for (int i = 766; i >= 0; i--)
// 	{
// 		sum += HistRGB[i];
// 		if (sum > row * col * 0.1)
// 		{
// 			Threshold = i;
// 			break;
// 		}
// 	}
// 	int AvgB = 0;
// 	int AvgG = 0;
// 	int AvgR = 0;
// 	int cnt = 0;
// 	for (int i = 0; i < row; i++)
// 	{
// 		for (int j = 0; j < col; j++)
// 		{
// 			int sumP = src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i, j)[2];
// 			if (sumP > Threshold)
// 			{
// 				AvgB += src.at<Vec3b>(i, j)[0];
// 				AvgG += src.at<Vec3b>(i, j)[1];
// 				AvgR += src.at<Vec3b>(i, j)[2];
// 				cnt++;
// 			}
// 		}
// 	}
// 	AvgB /= cnt;
// 	AvgG /= cnt;
// 	AvgR /= cnt;
// 	for (int i = 0; i < row; i++)
// 	{
// 		for (int j = 0; j < col; j++)
// 		{
// 			int Blue = src.at<Vec3b>(i, j)[0] * MaxVal / AvgB;
// 			int Green = src.at<Vec3b>(i, j)[1] * MaxVal / AvgG;
// 			int Red = src.at<Vec3b>(i, j)[2] * MaxVal / AvgR;
// 			if (Red > 255)
// 			{
// 				Red = 255;
// 			}
// 			else if (Red < 0)
// 			{
// 				Red = 0;
// 			}
// 			if (Green > 255)
// 			{
// 				Green = 255;
// 			}
// 			else if (Green < 0)
// 			{
// 				Green = 0;
// 			}
// 			if (Blue > 255)
// 			{
// 				Blue = 255;
// 			}
// 			else if (Blue < 0)
// 			{
// 				Blue = 0;
// 			}
// 			dst.at<Vec3b>(i, j)[0] = Blue;
// 			dst.at<Vec3b>(i, j)[1] = Green;
// 			dst.at<Vec3b>(i, j)[2] = Red;
// 		}
// 	}
// 	return dst;
// }