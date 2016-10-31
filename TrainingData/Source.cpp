
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

const int nTraining = 60000;

const int width = 28;
const int height = 28;
double maxAC = 90;
const int number_input = width * height; 
const int number_hidden = 128;
const int number_output = 10; 
const int epochs = 512;
const double learning_rate = 0.001;
const double momentum = 0.9;
const double epsilon = 0.001;


double m_weightHidden[number_input][number_hidden], delta1[number_input][number_hidden], input[number_input];

double m_weightOut[number_hidden][number_output], delta2[number_hidden][number_output], m_outHidden[number_hidden], m_errorHidden[number_hidden];


double  output[number_output], m_errorOut[number_output];
double expected[number_output];



ifstream image;
ifstream label;
ifstream imageTest;
ifstream labelTest;



void init_array() {

	for (int i = 0; i < number_input; ++i) {
		for (int j = 0; j < number_hidden; ++j) {
			int sign = rand() % 2;

	

			m_weightHidden[i][j] = (double)(rand() % 6) / 10.0;
			if (sign == 1) {
				m_weightHidden[i][j] = -m_weightHidden[i][j];
			}
		}
	}

	
	for (int i = 0; i < number_hidden; ++i) {
		for (int j = 0; j < number_output; ++j) {
			int sign = rand() % 2;

		

			m_weightOut[i][j] = (double)(rand() % 10 + 1) / (10.0 * number_output);
			if (sign == 1) {
				m_weightOut[i][j] = -m_weightOut[i][j];
			}
		}
	}
}

double sigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}
void perceptron() {


	for (int j = 0; j < number_hidden; ++j) {
		double total = 0;
		for (int i = 0; i < number_input; ++i) {

			total += input[i] * m_weightHidden[i][j];
		}
		m_outHidden[j] = sigmoid(total);
	}
	for (int j = 0; j < number_output; ++j) {
		double total = 0;
		for (int i = 0; i < number_hidden; ++i) {

			total += m_outHidden[i] * m_weightOut[i][j];
		}
		output[j] = sigmoid(total);
	}
}

double square_error(){
	double res = 0.0;
	for (int i = 0; i < number_output; ++i) {
		res += (output[i] - expected[i]) * (output[i] - expected[i]);
	}
	res *= 0.5;
	return res;
}
void back_propagation() {
	double sum;

	for (int i = 0; i < number_output; ++i) {
		m_errorOut[i] = output[i] * (1 - output[i]) * (expected[i] - output[i]);
	}

	for (int i = 0; i < number_hidden; ++i) {
		sum = 0.0;
		for (int j = 0; j < number_output; ++j) {
			sum += m_weightOut[i][j] * m_errorOut[j];
			delta2[i][j] = (learning_rate * m_errorOut[j] * m_outHidden[i]) + (momentum * delta2[i][j]);
			m_weightOut[i][j] += delta2[i][j];
		}
		m_errorHidden[i] = m_outHidden[i] * (1 - m_outHidden[i]) * sum;
	}
	for (int i = 0; i < number_input; ++i) {
		for (int j = 0; j < number_hidden; j++) {
			delta1[i][j] = (learning_rate * m_errorHidden[j] * input[i]) + (momentum * delta1[i][j]);
			m_weightHidden[i][j] += delta1[i][j];
		}
	}
}

int learning_process() {
	for (int i = 0; i < number_input; ++i) {
		for (int j = 0; j < number_hidden; ++j) {
			delta1[i][j] = 0.0;
		}
	}

	for (int i = 0; i < number_hidden; ++i) {
		for (int j = 0; j < number_output; ++j) {
			delta2[i][j] = 0.0;
		}
	}

	for (int i = 0; i < epochs; ++i) {
		perceptron();
		back_propagation();
		if (square_error() < 0.001) {
			return i;
		}
	}
	return epochs;
}

void getImage(int index){


	image.seekg(16 + index * number_input);
	char a[1];

	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 28; ++j) {
			image.read(a, 1);
			if (a[0] != 0)
				input[i * 28 + j] = 1.0;
			else
				input[i * 28 + j] = 0.0;

		}

	}

}
void getImageTest(int index){


	imageTest.seekg(16 + index * number_input);
	char a[1];

	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 28; ++j) {
			imageTest.read(a, 1);
			if (a[0] != 0)
				input[i * 28 + j] = 1.0;
			else
				input[i * 28 + j] = 0.0;
			cout << input[i * 28 + j];
		}
		cout << endl;
	}

}
void getLabel(int index){
	label.seekg(8 + index);
	char a[1];
	for (int i = 0; i < number_output; i++){
		expected[i] = 0.0;
	}
	label.read(a, 1);
	expected[a[0]] = 1.0;
}
double getLabelTest(int index){
	labelTest.seekg(8 + index);
	char a[1];
	for (int i = 0; i < number_output; i++){
		expected[i] = 0.0;
	}
	labelTest.read(a, 1);
	expected[a[0]] = 1.0;
	return a[0];
}
void write_matrix(string file_name) {
	ofstream file(file_name.c_str(), ios::out|ios::binary);
	for (int i = 0; i < number_input; ++i) {
		for (int j = 0; j < number_hidden; ++j) {
			file << m_weightHidden[i][j] << " ";
		}
		file << endl;
	}

	for (int i = 0; i < number_hidden; ++i) {
		for (int j = 0; j < number_output; ++j) {
			file << m_weightOut[i][j] << " ";
		}
		file << endl;
	}

	file.close();
}
double Test()
{
	int count = 0;
	for (int i = 0; i < 10000; i++){
		getImageTest(i);
		double value = getLabelTest(i);
		perceptron();
		double max = -1;
		int position = 0;
		for (int j = 0; j < number_output; j++)
		{
			if (output[j]>max){
				position = j;
				max = output[j];
			}
		}
		if (position == value){
			count++;
		}
	}
	double ac = count / 100.0;
	if (ac > maxAC)
	{
		write_matrix("dataTest.dat");
		maxAC = ac;
	}
	return ac;
}
void training()
{
	for (int sample = 1; sample <= nTraining; ++sample) {



		getImage(sample - 1);
		getLabel(sample - 1);
		
		int nIterations = learning_process();

		cout << "Error Image " << sample << ":" << square_error() << endl;
		cout << "So lan thuc hien:" << nIterations << endl;

		// Save the current network (weights)

	}

	{
		cout << "Ti le loi test" << Test() << endl;
	}


}

int main(int argc, char *argv[]) {



	image.open("train-images.idx3-ubyte", ios::in | ios::binary);
	label.open("train-labels.idx1-ubyte", ios::in | ios::binary);
	imageTest.open("t10k-images.idx3-ubyte", ios::in | ios::binary); 
	labelTest.open("t10k-labels.idx1-ubyte", ios::in | ios::binary); 

	init_array();

	training();

	
	image.close();
	label.close();
	system("pause");
	return 0;
}
