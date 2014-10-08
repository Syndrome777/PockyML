#include"ann_head.h"


ann_model::ann_model()
{
}

ann_model::ann_model(const mat& in_data, const vec& in_data_lab)
{
	input_data(in_data, in_data_lab);
}

ann_model::~ann_model()
{
}


void ann_model::input_data(const mat& in_data, const vec& in_data_lab)
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


void ann_model::init(const int node_n)
{
	node_num = node_n;

	int cnum = 0;
	for(int i = 0; i < label.size(); i++){
		if(!label_2_num[label[i]]){
			label_2_num[label[i]] = cnum;
			cnum++;
		}
	}
	class_num = cnum;


	for(int i = 0; i < dim_num; i++ ){
		vec temp;
		for(int j = 0; j < node_num; j++ )
			temp.push_back(get_rand());
		W.push_back(temp);
	}
	for(int i = 0; i < node_num; i++)
		W_a.push_back(get_rand());

	for(int i = 0; i < node_num; i++ ){
		vec temp;
		for(int j = 0; j < class_num; j++ )
			temp.push_back(get_rand());
		V.push_back(temp);
	}
	for(int i = 0; i < class_num; i++)
		V_b.push_back(get_rand());

}



void ann_model::train(const int node_n)
{
}



vec ann_model::prediction(const vec& in_data)
{
	//隐层节点数据
	vec mid;
	vec temp;
	vec resl;
	double mid_res;

	//输入层到隐层的映射，通过sigmoid函数
	for(int i = 0; i < node_num; i++){
		for(int j = 0; j < dim_num; j++)
			temp.push_back(W[j][i]);
		mid_res = multiplication(in_data, temp)- W_a[i];
		mid.push_back(sigmoid(mid_res));
		temp.clear();
	}

	//隐层到输出层的映射，通过sigmoid函数
	for(int i = 0; i < class_num; i++){
		for(int j = 0; j < node_num; j++)
			temp.push_back(V[j][i]);
		mid_res = multiplication(mid, temp) - V_b[i];
		resl.push_back(sigmoid(mid_res));
		temp.clear();
	}

	return resl;
}


void ann_model::correction()
{

}





double ann_model::error_all(const mat& res)
{
	double Eor = 0;
	for(int i = 0; i < samp_num; i++ ){
		Eor = Eor + error_one(label[i],res[i]);
	}
	return Eor;
}


double ann_model::error_one(const double lab, const vec& res)
{
	vec ans;
	for(int i = 0; i < class_num; i++){
		if(i != label_2_num[lab])
			ans.push_back(0);
		else
			ans.push_back(1);
	}

	double Eor = 0.0;
	for(int i = 0; i < samp_num; i++){
		Eor = Eor + 1.0 * (ans[i] - res[i]) * (ans[i] - res[i]);
	}
	Eor = Eor / (2 * class_num);
	return Eor;
}



inline double ann_model::sigmoid(const double x)
{
	return 1.0/(1+exp(-1.0*x));
}


inline double ann_model::get_rand()
{
	return 2.0*rand()/RAND_MAX - 1.0;
}



inline double multiplication(const vec& vec1, const vec& vec2)
{
	double res = 0;
	for(int i = 0; i < vec1.size(); i++){
		res = res + vec1[i] * vec2[i];
	}
	return res;
}







