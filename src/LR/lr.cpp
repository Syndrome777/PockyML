#include"lr_head.h"


lr_model::lr_model()
{
}

lr_model::lr_model(const mat& in_data, const vec& in_data_lab)
{
	input_data(in_data, in_data_lab);
}

lr_model::~lr_model()
{
}

void lr_model::init()
{
	for(int i = 0; i < dim_num; i++)
		W.push_back(get_rand());
	b = get_rand();

}

void lr_model::input_data(const mat& in_data, const vec& in_data_lab)
{
	samp_num = in_data.size();
	dim_num = in_data[0].size();
	for(int i = 0; i < in_data.size(); i++){
		vec temp;
		for(int j = 0; j < in_data[0].size(); j++)
			temp.push_back(in_data[i][j]);
		raw_data.push_back(temp);
		label.push_back(in_data_lab[i]);
	}
}

bool lr_model::train()
{
	
	return true;
}

vec lr_model::prediction(const mat& in_data)
{
	vec resl;
	double temp;
	for(int i = 0; i < in_data.size(); i++){
		temp = b;
		for(int j = 0; j < dim_num ; j++)
			temp += W[j] * in_data[i][j];
		resl.push_back(temp);
		
	}	
	return resl;
}


