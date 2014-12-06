#include"svm_head.h"
#include"libsvm_svm.h"

SVM_MODEL::SVM_MODEL()
{
}

SVM_MODEL::SVM_MODEL(const mat &in_data, const vec &in_data_lab)
{
	input_data(in_data, in_data_lab);
}

SVM_MODEL::~SVM_MODEL()
{
}

void SVM_MODEL::init()
{
}

void SVM_MODEL::init(const string &kernel_t)
{
	kernel = kernel_t;
}

bool SVM_MODEL::input_data(const mat &in_data, const vec &in_data_lab)
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
	return true;
}

bool SVM_MODEL::train()
{
	const char *error_msg;
	error_msg = svm_check_parameter(&prob, &param);
	if(error_msg){
		cout << *error_msg << endl;
		exit(1);
	}
	model = svm_train(&prob, &param);

	return true;
}

vec SVM_MODEL::prediction(const mat& in_data)
{
	vec resl;
	for(int i = 0; i < in_data.size(); i++){
		
	}

	return resl; 
}

vector<svm_model> mat_2_svm_model(const mat& in_data)
{
	vector<svm_model> data_node;
	for(int i = 0; i < in_data.size(); i++){
		svm_model temp;
		for(int j = 0; j < in_data[0].size(); j++){
			temp[j]
		}
	}
	
	return data_node;
}





