#define _CRT_SECURE_NO_WARNINGS
#include"Xulyanh.h"
#include<fstream>
#include<stack>
#include"NeuralNetwork.h"
#include"TinhToanBieuThuc.h"
#include<ctime>
#include<fstream>
#include<vector>
#define Image_count 60000
float input[784];
static int readBEInt(char *b, int start) {
	return (((b[start + 0] & 0xff) << 24) | ((b[start + 1] & 0xff) << 16)
		| ((b[start + 2] & 0xff) << 8) | ((b[start + 3] & 0xff)));
}

void tool()
{
	Xulyanh xuly("C:\\Users\\WinDown\\Desktop\\ghjk.png");
	xuly.Cat_anh();
	//xuly.ResizeImage();

	std::vector<Mat> listNumber;//lưu ảnh các số trong thư mục Data
	//INPUTLAYER ListMatrix[Image_count];//lưu lại các ma trận đã được chuyển đổi từ ảnh trong thư mục data
	//đọc các file ảnh tử thư mục data
	string link = "Data\\1-0";
	string link_temp = "Data\\1-A";
	for (int i = 0; i < Image_count; i++)
	{
		if (i % 260==0 && i!=0)
		{
			link_temp += "A";
		}
		if (i % 10 == 0&&i!=0)
		{
			link_temp[link_temp.length() - 1] += 1;
		}

		Mat tam;
		char s[1];
		s[0] = char(i % 10 + 48);
		string temp;
		temp.assign(s, 1);
		temp += ".jpg";
		link = link_temp + temp;
		tam = imwrite(link, xuly.listNumberCurrent[i]);
	}

}
string nhandang()
{
	Xulyanh xuly("C:\\Users\\WinDown\\Desktop\\asd1.png");
	xuly.Cat_anh();
	//xuly.ResizeImage();
	NeuralNetwork neuralNet = NeuralNetwork();
	neuralNet.DocTrongSo();
	char *dayso = new char[xuly.listNumberCurrent.size()];
	for (int i = 0; i < xuly.listNumberCurrent.size(); i++)
	{
		//INPUTLAYER input1;
		//ArrayChar out;
	//	ConvertToMatrix(xuly.listNumberCurrent[i], input1);
		//neuralNet.setinput(input1);
		neuralNet.test();
		//CopyArray(neuralNet.out, out);
		int char_ = 0;
		
		dayso[i] = char_;
	}
	string daysotemp;
	daysotemp.assign(dayso, xuly.listNumberCurrent.size());
	imshow("anh goc", xuly.source);
	return daysotemp;
}

void load1(){
	ifstream is;
	ofstream os;
	os.open("testMnist.dat", ios::out | ios::binary);
	is.open("t10k-images.idx3-ubyte", ios::in | ios::binary);
	if (!is.is_open()){
		cout << "sadsadsa";
	}
	
	char s[4];
	int NumberImage;
	int magic;
	int height;
	int width;
	char asdasdas[1];
	is.read(s, 4);
	os.write(s, 4);
	magic = readBEInt(s, 0);
	
	is.read(s, 4);
	os.write(s, 4);
	NumberImage = readBEInt(s, 0);
	
	is.read(s, 4);
	height = readBEInt(s,0);
	is.read(s, 4);
	width = readBEInt(s, 0);
	int size = width*height;
	asdasdas[0] = 16;
	os.write(asdasdas, 1);
	os.write(asdasdas, 1);
	float dummy_query_data[784];
	for (int i = 0; i < NumberImage; i++){

		for (int j = 0; j < width; j++){
			for (int k = 0; k < height; k++)
			{
				char asd[1];
				is.read(asd, 1);

				int number = asd[0];
				if (number < 0)
					dummy_query_data[j*height + k] = number + 256;
				else
					dummy_query_data[j*height + k] = number;
			}
		}

		Mat im = Mat(height, width, CV_32F, &dummy_query_data);
		
		Xulyanh assd = Xulyanh();
		assd.source = im;
		assd.Cat_anh();
		assd.ResizeImage(16, 16);
		imshow("asd", assd.listNumberCurrent[0]);
		for (int i = 0; i < assd.listNumberCurrent[0].cols; i++)
		{
			for (int j = 0; j < assd.listNumberCurrent[0].rows; j++)
			{
				float colour = assd.listNumberCurrent[0].at<float>(Point(i, j));
				char asdasdas[1];
				if (colour != 0)
				{

					asdasdas[0] = 1;
					os.write(asdasdas, 1);
				}
				else
				{
					asdasdas[0] = 0;
					os.write(asdasdas, 1);
				}
			}
			//imshow("sadsadsa", im);
		}
	}
	os.close();
	is.close();
	//std::ifstream in;
	//in.open("Data\\data.txt", std::ios::in);
	//std::vector<std::string> listchar;
	//while (!in.eof())
	//{
	//	std::string temp;
	//	std::getline(in, temp);
	//	listchar.push_back(temp);
	//}
	//ArrayChar arrayBinary[18];
	//for (int i = 0; i < listchar.size(); i++)
	//{
	//	ArrayChar temp_;
	//	ConvertToByte((int)listchar[i][0], temp_);
	//	for (int j = 0; j < 16; j++)
	//	{
	//		arrayBinary[i][j] = temp_[j];
	//	}
	//}
}


int main()
{
	clock_t start, end;
	start = clock();

	NeuralNetwork neuralNet = NeuralNetwork();
	neuralNet.DocTrongSo();
	
	Mat imsd = imread("Untitled.png", CV_8UC1);
	
	Xulyanh xuly = Xulyanh();
	xuly.source = imsd;
	xuly.Cat_anh();
	xuly.ResizeImage(16,16);
	ofstream os;
	os.open("dataTest.dat", ios::out | ios::binary);
	char s[1];
	s[0] = xuly.listNumberCurrent.size();
	os.write(s, 1);

	for (int i = 0; i < xuly.listNumberCurrent.size(); i++)
	{
		for (int j = 0; j < xuly.listNumberCurrent[i].cols; j++){
			char s[1];
			s[0] = char(i + 48);
			string temp;
				temp.assign(s, 1);
				temp += ".jpg";
				imshow(temp, xuly.listNumberCurrent[i]);
			for (int k = 0; k < xuly.listNumberCurrent[i].rows; k++)
			{
				Scalar colour = xuly.listNumberCurrent[i].at<uchar>(Point(k, j));
				if (colour[0] != 255)//nếu là màu đen
				{
					s[0] = 1;
					os.write(s, 1);
					input[(j + 6) * 28 + (k + 6)] = 1;
				}
				else
				{
					s[0] = 0;
					os.write(s, 1);
					input[(j + 6) * 28 + (k + 6)] = 0;
				}
				
			}
			
		}
		for (int j = 0; j < 28; j++){

			for (int k = 0; k < 28; k++)
			{
				cout << input[j * 28 + k];
			}
			cout << endl;
		}
		cout << endl;
		cout << neuralNet.nhandang(input) << endl;
	}
	os.close();
	

	
	end = clock();
	
	waitKey();
system("pause");
	return 1;
}


