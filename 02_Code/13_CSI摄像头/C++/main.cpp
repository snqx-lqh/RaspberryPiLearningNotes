#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;  
using namespace cv;  
  
int main(int argc, char** argv)  
{  
    // 打开视频文件  
    VideoCapture cap(0);  
  
    // 检查是否成功打开视频文件  
    if (!cap.isOpened())  
    {  
        std::cerr << "无法打开视频文件" << std::endl;  
        return -1;  
    }  
  
    // 设置窗口大小  
    namedWindow("Video", WINDOW_NORMAL);  
    resizeWindow("Video", 400, 400);  
  
    // 循环播放视频直到按下退出键  
    while (true)  
    {  
        Mat frame;  
  
        // 从视频文件中读取下一帧  
        cap >> frame;  
  
        // 如果读取的帧为空，则视频播放结束，退出循环  
        if (frame.empty())  
            break;  
  
        // 在窗口中显示当前帧  
        imshow("Video", frame);  
  
        // 等待一段时间，然后继续循环（按Q键退出）  
        if (waitKey(30) == 'q' || waitKey(30) == 27) // 'q'键或Esc键  
            break;  
    }  
  
    // 释放视频文件和窗口资源  
    cap.release();  
    destroyAllWindows();  
  
    return 0;  
}