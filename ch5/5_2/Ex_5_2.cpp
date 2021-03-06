#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main( int argc, const char** argv )
{
    cv::Mat m(100, 100, CV_8UC3);
    m = 0;
    for(int i = 20; i < 40; i++)
    {
        for(int j = 5; j < 20; j++)
        {
            m.at<cv::Vec3b>(i, j)[1] = 255;
        }
    }
    cv::namedWindow("Ex_5_2", cv::WINDOW_AUTOSIZE);
    cv::imshow("Ex_5_2", m);
    cv::waitKey(0);
    return 0;
}