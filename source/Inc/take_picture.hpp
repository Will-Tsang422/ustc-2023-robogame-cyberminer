#include <opencv2/opencv.hpp>
#include <cstring>
#include <wiringPi.h>

using namespace std;
using namespace cv;

int take_picture(string name)
{
    VideoCapture video(0);
    if (!video.isOpened())
    {
        cout << "\033[41m摄像头打开失败！\033[0m" << endl;
        return -1;
    }
    delay(3000);
    Mat img;
    if (!video.read(img))
    {
        cout << "\033[41m图像读取失败！\033[0m" << endl;
        return -2;
    }
    if (!imwrite(name, img))
    {
        cout << "\033[41m图片保存失败！\033[0m" << endl;
        return -3;
    }
    cout << name << "保存成功！" << endl;
    // 退出程序时刻自动关闭视频流
    video.release();
    return 0;
}