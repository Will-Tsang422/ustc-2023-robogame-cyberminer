#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace cv;


extern void mouse(int event, int x, int y, int flags, void* param)
{
	if (event == EVENT_LBUTTONDOWN) //单击鼠标左键保存图片
	{
		Mat img = *(Mat*)param;
		time_t now = time(nullptr);
		tm *local = localtime(&now);

		string name = to_string(1 + local->tm_mon) + "月" + to_string(local->tm_mday) + "日" + to_string(local->tm_hour) + "时" + to_string(local->tm_min) + "分.jpg";
		imwrite(name, img);
		cout << name + " 已保存" << endl;
	}
}

int main()
{
	VideoCapture video(0);
	if (!video.isOpened())
	{
		cout << "摄像头打开失败！" << endl;
		return -1;
	}
	while (1)
	{
		Mat img;
		video >> img;
		imshow("Live", img);  //显示图像

		setMouseCallback("Live", mouse, &img);
		char c = waitKey(50);
		if (c == 27)  //按ESC按键退出视频保存
		{
			break;
		}
	}
	// 退出程序时刻自动关闭视频流
	video.release();
	return 0;

}