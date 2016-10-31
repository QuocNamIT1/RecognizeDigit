#include "NeuralNetwork.h"
Neural::Neural(){}
Neural::~Neural(){}
double e = std::exp(1.0);


NeuralNetwork::NeuralNetwork()
{
	
	srand(time(NULL));
	for (int i = 0; i < _INPUTLAYER; i++)
	{
		for (int j = 0; j < _HIDELAYER; j++)
		{
			{double weight;
			do
			{
				int temp = (rand() % 6);
				weight = (double)temp / 10.0;
			} while (!weight);
			int sign = rand() % 2;
			if (sign == 1){
				m_hideWeight[i][j] = (-weight);
			}
			else
				m_hideWeight[i][j] = (weight);
			}
			
		}
	}
	for (int i = 0; i < _INPUTLAYER; i++)
	{
		for (int j = 0; j < _HIDELAYER; j++)
		{
			delta1[i][j] = 0;
		}
	}
	for (int i = 0; i < _HIDELAYER; i++)
	{
		for (int j = 0; j < _OUTPUTLAYER; j++)
		{
			double weight;
			do
			{
				int temp = (rand() % 6);
				weight = ((double)temp) / 10.0;
			} while (!weight);
			int sign = rand() % 2;
			if (sign == 1){
				m_outWeight[i][j] = (-weight);
			}else
		 	m_outWeight[i][j]= (weight);
			delta2[i][j] = 0.0;
		}
	}
}
void NeuralNetwork::GhiTrongSo()
{
	std::ofstream os("Data\\Test.txt");
	//os << _HIDELAYER << std::endl;
	for (int i = 0; i < _INPUTLAYER; i++)
	{
		for (int j = 0; j < _HIDELAYER; j++)
		{
			os << m_hideWeight[i][j]<<" ";
		}
		os << std::endl;
	}
	for (int i = 0; i < _HIDELAYER; i++)
	{
		for (int j = 0; j < _OUTPUTLAYER; j++)
		{
			os << m_outWeight[i][j] << " ";
		}
		os << std::endl;
	}
}
void NeuralNetwork::DocTrongSo()
{
	std::ifstream os("dataTest.txt",ios::in);
	if (!os.is_open()){
		return;
	}
	for (int i = 0; i < _INPUTLAYER; i++)
	{
		for (int j = 0; j < _HIDELAYER; j++)
		{
			os >> m_hideWeight[i][j];
		}
	}
	for (int i = 0; i < _HIDELAYER; i++)
	{
		for (int j = 0; j < _OUTPUTLAYER; j++)
		{
			os >> m_outWeight[i][j];
		}
	}
}
double NeuralNetwork::training(int count_image)
{
	double total_error;
	//số vòng huấn luyện
	for (int j = 0; j < count_image; ++j)
	{
		total_error = 0;
	for (int i = 0; i < 500; ++i)
	{
		double error ;
		
		//duyệt qua list các ảnh dữ liệu
		
			
			double total_weight1 = 0;
			double total_weight;
			error = 0;
			double value[_INPUTLAYER];
			double arraybyte[_OUTPUTLAYER];
			for (int i = 0; i < _OUTPUTLAYER; i++)
			{
				arraybyte[i] = 0.0;
			}
			getImage("train-images.idx3-ubyte",j, value);
			getLabel("train-labels.idx1-ubyte",j, arraybyte);
			//duyệt trong 250 neural ẩn
			for (int m = 0; m < _HIDELAYER; ++m)
			{
				total_weight = -0;
				for (int k = 0; k < _INPUTLAYER; ++k)
				{
					total_weight += value[k] * m_hideWeight[k][m];
				}
				//total_weight -= 30;
				//sau khi tính tổng các input voi trong so tai neural m thì tính đầu ra tại neural này
				m_hideOut[m] = 1.0 / (1.0 + std::pow(e, -lmbda*total_weight));
			}//end lớp ẩn
			//duyệt qua _OUTPUTLAYER neural lớp ra
			for (int n = 0; n < _OUTPUTLAYER; ++n)
			{
				total_weight1 = -0;
				for (int l = 0; l < _HIDELAYER; ++l)
				{
					total_weight1 += m_outWeight[l][n] * m_hideOut[l];
				}
				//total_weight1 -= 30;
				m_outOut[n] = 1.0 / (1.0 + std::pow(e, -lmbda * total_weight1));
				error += 1.0 / 2 * std::pow((arraybyte[n] - m_outOut[n]), 2);
				float daoham1 = lmbda* m_outOut[n] * (1 - m_outOut[n]);
				m_outError[n] = (arraybyte[n] - m_outOut[n])*daoham1;
			}//end lớp ra
			//cập nhật trọng số cho lớp ra
			total_error += error;
			if (error >= 0.001)
			{
				//tính hệ số lỗi cho lớp ẩn
				for (int m = 0; m < _HIDELAYER; ++m)
				{
					float daoham = lmbda*(1 - m_hideOut[m])*m_hideOut[m];
					double delta = 0;
					for (int n = 0; n < _OUTPUTLAYER; ++n)
					{
						
						delta += m_outError[n] * m_outWeight[m][n];
						delta2[m][n]= learRate * m_outError[n] * m_hideOut[m]+0.9*delta2[m][n];
						m_outWeight[m][n] += delta2[m][n];
					}	//duyệt trong 250 neural ẩn
					m_hideError[m] = daoham*delta;
				}//end hệ số lỗi

				double totaltemp = 0;
				//cập nhật trọng số ch lớp ẩn
				for (int n = 0; n < _HIDELAYER; ++n)
				{
					for (int k = 0; k < _INPUTLAYER; ++k)
					{
						delta1[k][n]= learRate * value[k] * m_hideError[n]+0.9*delta1[k][n];
						m_hideWeight[k][n] += delta1[k][n];
					}
				}

			}
		}
		cout << "Ti le loi anh thu "<< j<<":"<<total_error <<endl;
	}
	return total_error;
}
double NeuralNetwork::nhandang(float input[])
{
	double total_weight1 = 0;
	double total_weight;
	double error = 0;
	double count = 0;
		for (int m = 0; m < _HIDELAYER; m++)
		{
			total_weight = 0;
			for (int k = 0; k < _INPUTLAYER; k++)
			{
				total_weight += input[k] * m_hideWeight[k][m];
			}
			//total_weight -= 30;
			//sau khi tính tổng các input voi trong so tai neural m thì tính đầu ra tại neural này
			m_hideOut[m] = 1.0 / (1.0 + std::pow(e, -lmbda*total_weight));
		}//end lớp ẩn
		double output[_OUTPUTLAYER];
		for (int n = 0; n < _OUTPUTLAYER; n++)
		{
			total_weight1 = 0;
			for (int l = 0; l < _HIDELAYER; l++)
			{
				total_weight1 += m_outWeight[l][n] * m_hideOut[l];
			}
			//total_weight1 -= 30;
			m_outOut[n] = 1.0 / (1.0 + std::pow(e, -lmbda * total_weight1));

			
		}
		double max = -1;
		int position = 0;
		for (int j = 0; j < _OUTPUTLAYER; j++)
		{
			if (m_outOut[j]>max){
				position = j;
				max = m_outOut[j];
			}
		}
		
	
		return position;
}
double NeuralNetwork::test()
{
	double total_weight1 = 0;
	double total_weight;
	double error = 0;
	double count = 0;
	for (int j = 0; j < 10000; ++j)
	{
		
		double total_weight1 = 0;
		double total_weight;
		error = 0;
		double value[_INPUTLAYER];
		double arraybyte[_OUTPUTLAYER];
		for (int i = 0; i < _OUTPUTLAYER; i++)
		{
			arraybyte[i] = 0.0;
		}
		getImage("t10k-images.idx3-ubyte",j, value);
		int output=getLabel("t10k-labels.idx1-ubyte",j, arraybyte);
		for (int jj = 0; jj < 28; jj++){

			for (int k = 0; k < 28; k++)
			{
				cout << value[jj * 28 + k];
			}
			cout << endl;
		}
		cout << endl;
		Sleep(1000);
		for (int m = 0; m < _HIDELAYER; m++)
		{
			total_weight = 0;
			for (int k = 0; k < _INPUTLAYER; k++)
			{
				total_weight += value[k] * m_hideWeight[k][m];
			}
			//total_weight -= 30;
			//sau khi tính tổng các input voi trong so tai neural m thì tính đầu ra tại neural này
			m_hideOut[m] = 1.0 / (1.0 + std::pow(e, -lmbda*total_weight));
		}//end lớp ẩn
		for (int n = 0; n < _OUTPUTLAYER; n++)
		{
			total_weight1 = 0;
			for (int l = 0; l < _HIDELAYER; l++)
			{
				total_weight1 += m_outWeight[l][n] * m_hideOut[l];
			}
			//total_weight1 -= 30;
			m_outOut[n] = 1.0 / (1.0 + std::pow(e, -lmbda * total_weight1));

			
		}
		double max = -1;
		int position = 0;
		for (int j = 0; j < _OUTPUTLAYER; j++)
		{
			if (m_outOut[j]>max){
				position = j;
				max = m_outOut[j];
			}
		}
		if (position == output){
			count++;
		}
	}
	return count/10000.0;
}
NeuralNetwork::~NeuralNetwork()
{

}
