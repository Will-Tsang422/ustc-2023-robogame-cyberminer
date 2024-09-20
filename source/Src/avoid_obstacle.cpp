#include "../Inc/avoid_obstacle.hpp"

void detect_obstacle(Mat& img)
{
	//if (temp.empty())
	//{
	//	cout << "图片加载失败" << endl;
	//	return Rect();
	//}
	Size origin_size = img.size();
	Size shrink_size = img.size();
	Size best_size;
	double ks = 1.1;
	Mat result;
	Mat shrink = img.clone();
	double minVal, maxVal, maxall;
	Point minLoc, maxLoc;
	for(int i = 0; i < 5; i++)
	{
		shrink_size.width *= ks;
		shrink_size.height *= ks;
		resize(shrink, shrink, shrink_size);
		matchTemplate(shrink, temp, result, TM_CCOEFF_NORMED);
		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
		if(i == 0)
		{
			maxall = maxVal;
			best_size = shrink_size;
		}
		else if (maxVal > maxall)
		{
			maxall = maxVal;
			best_size = shrink_size;
		}
	}
	resize(img, img, best_size);
	matchTemplate(img, temp, result, TM_CCOEFF_NORMED);
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
	rectangle(img, Rect(maxLoc.x, maxLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 1, 8);
	resize(img, img, origin_size);
	// cout << "最大匹配值：" << maxVal << " 所在位置" << maxLoc << endl;
}

void findcontours(Mat& image, vector<vector<Point>>& contours)
{
	Mat gray, binary;
	vector<Vec4i> hierarchy;
	//图像灰度化
	cvtColor(image, gray, COLOR_BGR2GRAY);
	//图像二值化
	threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
	imshow("binary", binary);
	//寻找轮廓
	findContours(binary, contours, hierarchy, 0, 2);
}

int Humoment_detect(Mat img)
{
	if (temp.empty())
	{
		cout << "请确认图像文件名称是否正确" << endl;
		return -1;
	}

	// 轮廓提取
	vector<vector<Point>> contours1;
	vector<vector<Point>> contours2;
	findcontours(img, contours1);
	findcontours(temp, contours2);
	cout << contours2.size() << endl;
	// hu矩计算
	Moments mm2 = moments(contours2[0]);
	Mat hu2;
	HuMoments(mm2, hu2);
	// 轮廓匹配
	for (int n = 0; n < contours1.size(); n++)
	{
		Moments mm = moments(contours1[n]);
		Mat hum;
		HuMoments(mm, hum);
		//Hu矩匹配
		double dist = matchShapes(hum, hu2, CONTOURS_MATCH_I1, 0);
		if (dist < 0.1)
		{
			drawContours(img, contours1, n, Scalar(0, 0, 255), 3, 8);
		}
	}
	return 0;
}
