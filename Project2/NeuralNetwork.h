#pragma once
#include<vector>
#include<ctime>
#include<math.h>
#include<Windows.h>
#include<fstream>
#include<iostream>
#define _HIDELAYER 128 
#define _INPUTLAYER 784 
#define _OUTPUTLAYER 10 
using namespace std;
class Neural
{
public:
	double *weight;
	double m_output;
	double m_error;
	Neural();
	~Neural();

private:

};

//typedef float INPUTLAYER[_INPUTLAYER];//ma trận input của lớp vào
typedef float HIDELAYER_WEIGHT[_INPUTLAYER][_HIDELAYER];//ma trận trọng số lớp ẩn
typedef float HIDELAYER_OUTPUT[_HIDELAYER];//ma trận output lớp ẩn
typedef float OUTPUTLAYER_WEIGHT[_HIDELAYER][_OUTPUTLAYER];//ma trận trọng số lớp ra
typedef float OUTPUTLAYER_OUTPUT[_OUTPUTLAYER];//ma trận output lớp ra
typedef float OUTPUTERROR[_OUTPUTLAYER];//mảng hệ số lỗi của lớp ra
typedef float HIDEERROR[_HIDELAYER];//mảng hệ số lỗi của lớp ẩn


//mạng neural
class NeuralNetwork
{
	float learRate = 0.001;
	float lmbda = 1.0;
	HIDELAYER_WEIGHT m_hideWeight;
	OUTPUTLAYER_WEIGHT m_outWeight;
	HIDELAYER_OUTPUT m_hideOut;
	OUTPUTLAYER_OUTPUT m_outOut;
	HIDEERROR m_hideError;
	OUTPUTERROR m_outError;
	float delta1[_INPUTLAYER][_HIDELAYER];
	float delta2[_HIDELAYER][_OUTPUTLAYER];
public:
	//int Count_hideLayer;//số neural lớp ẩn
	int Count_OutLayer;//số neural lớp ra
	
	NeuralNetwork();
	double training(int count);
	double test();
	double nhandang(float input[]);
	void GhiTrongSo();
	void DocTrongSo();
	int ConvertToChar_( double bytechar[])
	{
		int char_=0;
		for (int i = 0; i < _OUTPUTLAYER; i++)
		{
			char_ += bytechar[i] * std::pow(2, 15 - i);
		}
		return char_;
	}
	void getImage(string path,int index, double value[]){
		ifstream is;

		is.open(path, ios::in | ios::binary);
		
		is.seekg(16 + index * _INPUTLAYER);
		char a[1];
		for (int i = 0; i < _INPUTLAYER; i++){
			is.read(a, 1);
			if (a[0] != 0)
				value[i] = 1;
			else
				value[i] = 0;
		}

	}
	
	double getLabel(string path,int index, double value[])
	{
		ifstream is;

		is.open(path, ios::in | ios::binary);

		is.seekg(8 + index);
		char a[1];
		
			is.read(a, 1);
			value[a[0]] = 1.0;
			return a[0];
		}

	
	~NeuralNetwork();
};

