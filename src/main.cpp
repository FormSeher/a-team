/*
 * main.cpp
 *
 * Created on: 21.03.2014
 * Author: scar, Simon Kerler
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cout <<" Usage: display_image ImageToLoadAndDisplay" << std::endl;
		return -1;
	}

	cv::Mat image;
	image = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);

	if(!image.data)
	{
		std::cout <<  "Could not open or find the image" << std::endl;
		return -1;
	}

	cv::namedWindow("Display window");
	cv::imshow("Display window", image);

	cv::waitKey(0);
	return 0;
}