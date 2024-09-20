#include "../Inc/detect_color.hpp"
#include <wiringPi.h>
#include <cstring>

vector<Rect> find_color(Mat img, COLOR color)
{
	Mat hsv;
	cvtColor(img, hsv, COLOR_BGR2HSV_FULL);
	inRange(hsv, color_low[color], color_high[color], hsv);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(hsv, hsv, MORPH_OPEN, kernel);
	vector<vector<Point>> contours;
	findContours(hsv, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	vector<Rect> rects;
	for (int i = 0; i < contours.size(); i++)
	{
		Rect rect = boundingRect(contours[i]);
		if (rect.area() > MIN_AREA)
		{
			rects.push_back(rect);
		}
	}
	return rects;
}

bool detect_color(Mat img, COLOR color)
{
	Mat hsv;
	cvtColor(img, hsv, COLOR_BGR2HSV_FULL);
	Mat result;
	inRange(hsv, color_low[color], color_high[color], hsv);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(hsv, hsv, MORPH_OPEN, kernel, Point(-1, -1), 2);
	morphologyEx(hsv, hsv, MORPH_CLOSE, kernel, Point(-1, -1), 2);
	imwrite("/home/cyberminer/robogame/pictures/inrange" + ore[color] + ".jpg", hsv);
	vector<vector<Point>> contours;
	findContours(hsv, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	vector<Rect> rects;
	for (int i = 0; i < contours.size(); i++)
	{
		Rect rect = boundingRect(contours[i]);
		if (rect.area() > MIN_AREA)
		{
			cout << rect.area() << endl;
			return rect.area();
		}
	}
	return false;
}

// vector<RotatedRect> find_color_rotated(Mat img, COLOR color)
// {
// 	Mat hsv;
// 	cvtColor(img, hsv, COLOR_BGR2HSV_FULL);
// 	inRange(hsv, color_low[color], color_high[color], hsv);
// 	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
// 	morphologyEx(hsv, hsv, MORPH_OPEN, kernel);
// 	// imshow("hsv", hsv);
// 	vector<vector<Point>> contours;
// 	findContours(hsv, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
// 	vector<RotatedRect> rects;
// 	for (int i = 0; i < contours.size(); i++)
// 	{
// 		RotatedRect rect = minAreaRect(contours[i]);
// 		double area = rect.size.area();
// 		if (area > MIN_AREA)
// 		{
// 			rects.push_back(rect);
// 		}
// 	}
// 	return rects;
// }

// bool sort_ores(Mat img, uint8_t writebuf[])
// {
// 	auto begin = chrono::high_resolution_clock::now();
// 	vector<Ore> blues = find_color(img, BLUE);
// 	vector<Ore> oranges = find_color(img, ORANGE);
// 	blues.insert(blues.end(), oranges.begin(), oranges.end());
// 	if (blues.size() != 5)
// 		return false;
// 	sort(blues.begin(), blues.end());
// 	// for (int i = 0; i < blues.size(); i++)
// 	// {
// 	// 	cout << blues[i].rect.x << " ";
// 	// }
// 	writebuf[0] = writebuf[6] = 0xFF;
// 	for (int i = 1; i <= 5; i++)
// 	{
// 		writebuf[i] = blues[i].color;
// 	}
// 	auto end = chrono::high_resolution_clock::now();
// 	auto interval = chrono::duration_cast<chrono::milliseconds>(end - begin);
// 	cout << __func__ << " cost: " << interval.count() << endl;
// 	for (int i = 0; i < 5; i++)
// 	{
// 		cout << ore[blues[i].color] << ' ';
// 	}
// 	cout << endl;
// 	return true;
// }

int sort_fuels(Mat img, uint8_t writebuf[])
{
	vector<Rect> purples = find_color(img, PURPLE);
	if (purples.size() != 2)
		return -1;
	printf("x1:%d x2:%d x1width:%d x2width:%d img.cols:%d\n", purples[0].x, purples[1].x, purples[0].width, purples[1].width, img.cols);
	int gap = abs(purples[0].x - purples[1].x);
	int width = (purples[0].width + purples[1].width) / 2;
	if (gap > 2 * width)
	{
		writebuf[0] = writebuf[2] = PURPLE + 1;
		writebuf[1] = 5;
	}
	else if (min(purples[0].x, purples[1].x) + width < img.cols / 2)
	{
		writebuf[0] = writebuf[1] = PURPLE + 1;
		writebuf[2] = 5;
	}
	else if (max(purples[0].x, purples[1].x) > img.cols / 2)
	{
		writebuf[1] = writebuf[2] = PURPLE + 1;
		writebuf[0] = 5;
	}
	else
		return 0;
	return 1;
}

// void draw_rotatedrect(Mat &img, RotatedRect rect)
// {

// 	Point2f vertices[4];
// 	rect.points(vertices);
// 	for (int j = 0; j < 4; j++)
// 	{
// 		line(img, vertices[j], vertices[(j + 1) % 4], Scalar(0, 0, 255), 1, 8);
// 	}
// }

// void add_text(Mat &img, COLOR color, Point2f point)
// {
// 	putText(img, ore[color], point, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, 8);
// 	cout << "检测到" << ore_CN[color] << "矿石\r";
// }
