#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include<opencv\cv.h>
#include<opencv\highgui.h>
#include<opencv\cxcore.h>
#include<string>
using namespace cv;
class Xulyanh
{
public:
	Mat source;
	std::vector<Mat> listNumberCurrent;
	Xulyanh(string filename);
	Xulyanh();
	Mat ThresholdImage();
	void Cat_anh();
	void ResizeImage(int,int);
	~Xulyanh();
};

