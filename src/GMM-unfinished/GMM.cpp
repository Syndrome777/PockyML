#include"GMM_head.h"



GMM_model::GMM_model()
{
}

GMM_model::GMM_model(const mat& in_data)
{
	input_data(in_data);
}

GMM_model::~GMM_model()
{
}

void GMM_model::input_data(const mat& in_data)
{
	samp_num = in_data.size();
	dim_num = in_data[0].size();
	for(int i = 0; i < in_data.size(); i++){
		vec temp;
		for(int j = 0; j < in_data[i].size(); j++)
			temp.push_back(in_data[i][j]);
		raw_data.push_back(temp);
	}

}

void GMM_model::train(const int g_num)
{
}

double GMM_model::probability(const vec& sample)
{
}

void GMM_model::display()
{
}

double GMM_model::get_prob(const int i, const int k)
{
}

void GMM_model::adjust_para()
{
}


inline double gaussian(const vec& x_data, const vec& mu, const mat& sigma)
{
	double gaus;
	int n = x_data.size();
	MatrixXd sig(n,n);
	MatrixXd m(1,n);
	MatrixXd x(1,n);

	//数据导入
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			sig(i,j) = sigma[i][j];
		m(0,i) = mu[i];
		x(0,i) = x_data[i];
	}
	
	MatrixXd mid1(1,n);
	MatrixXd mid2(n,1);
	mid1 = x - m;//样本和均值的差，1*n
	mid2 = mid1.transpose();//转置，n*1

	MatrixXd mid3(1,1);//求解矩阵的值

	mid3 = (mid1 * sig.inverse() * mid2);
	
	gaus = 1.0 / sqrt( pow(2*PI, n)*sig.determinant() );
	gaus = gaus * exp( -0.5 * mid3(0,0) );

	return gaus;
}


