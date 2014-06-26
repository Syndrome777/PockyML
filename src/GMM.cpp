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


int test_main()
{
	return 0;
}





