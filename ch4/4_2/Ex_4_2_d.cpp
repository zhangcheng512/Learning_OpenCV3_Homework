#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;

void help()
{
	cout << "Original and integral image. Input 4 times '0' to quit." << endl;
	cout << "Input 4 arguments, left, up, right, down position of one rectangle to calculate the sum of pixels in that rectangle." << endl;
}

const int display_height = 200;
const int display_width = 100;

int main( int argc, char** argv) 
{
	// init numbers and display
	help();
	cv::Mat1b original_image(display_height, display_width);
	cv::Mat1f integral_image_for_display(display_height, display_width);
	cv::Mat1f integral_image_for_calculate(display_height, display_width);
	cv::RNG rng(0);
	rng.fill(original_image, cv::RNG::UNIFORM, 0, 255);
	integral_image_for_calculate = 0;

	cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Original Image",original_image);

	for(int i = 0; i < display_height ; i++)
	{
		integral_image_for_calculate.at<float>(i, 0) = cv::sum(original_image.rowRange(0, i + 1).colRange(0, 1))[0];
	}
    for(int i = 0; i < display_width ; i++)
	{
		integral_image_for_calculate.at<float>(0, i) = cv::sum(original_image.rowRange(0, 1).colRange(0, i + 1))[0];
	}
	for(int i = 1; i < display_height; i++)
	{
		for(int j = 1; j < display_width; j++)
		{
			integral_image_for_calculate.at<float>(i, j) = (float)original_image.at<uchar>(i, j) + integral_image_for_calculate.at<float>(i - 1, j) + integral_image_for_calculate.at<float>(i, j - 1) - integral_image_for_calculate.at<float>(i - 1, j - 1);
		}
	}
	integral_image_for_display = integral_image_for_calculate/integral_image_for_calculate.at<float>(display_height - 1, display_width - 1);

	cv::namedWindow("Integral Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Integral Image",integral_image_for_display);
	
	cout << "Press any key to start calculation, or 'ESC' to quit." << endl;
	char ch = cv::waitKey(0);
	if(ch == 27)
		return 1;

	unsigned left, up, right, down;
	cout << "Input left position: ";
	while(cin >> left)
	{
		cout << "Input up position: ";
		cin >> up;
		cout << "Input right position: ";
		cin >> right;
		cout << "Input down position: ";
		cin >> down;
		if(!(left || up || right || down))
			break;
		else
		{
			try
			{
				cout << integral_image_for_calculate.at<float>(down, right) - \
					integral_image_for_calculate.at<float>(down, left) - \
					integral_image_for_calculate.at<float>(up, right) + \
					integral_image_for_calculate.at<float>(up, left) << endl;
			}
			catch (const std::exception&)
			{
				CV_Error(1, "Input is not in range.");
			}
		}
		cout << "Input left position: ";
	}
	
	return 0;
}