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
	max_iter = 1000;
	learn_rate = 0.1;
	max_loss = 0.1;
	int iter_num = 0;
	vec loss;

	while(iter_num < max_iter){
		iter_num++;
		double learn_rate_u = learn_rate / (1 + 0.01*iter_num);
		for(int i = 0; i < samp_num; i++){
			loss.push_back(multiplication(W, raw_data[i]) + b - label[i]);
		}

		for(int i = 0 ; i < dim_num; i++){
			double tmp = 0;
			for(int j = 0; j < samp_num; j++)
				tmp += raw_data[j][i] * loss[j];
			W[i] -= learn_rate_u * (tmp/samp_num);
			//cout << "the gradient is :" << tmp / samp_num << endl;
		}
		double tmp = 0;
		for(int j = 0; j < samp_num; j++)
			tmp += loss[j];
		b -= learn_rate_u * (tmp/samp_num);

		cout << "the loss is :" << tmp << endl;
		if (fabs(tmp) < max_loss)
			break;
		loss.clear();	
	}
	cout << "training is finished!" << "The iteration is: " << iter_num << endl;
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

void lr_model::display()
{
	cout << "the W is:" << endl;
	for (int i = 0; i < W.size(); i++)
		cout << W[i]<<" ";
	cout << endl << "the b is:" << endl;
	cout << b << endl;
}

inline double multiplication(const vec& vec1, const vec& vec2)
{
	double res = 0;
	for(int i = 0; i < vec1.size(); i++){
		res = res + vec1[i] * vec2[i];
	}
	return res;
}


