#include"nb_head.h"


nb_model::nb_model()
{
}


nb_model::nb_model(const mat& in_data, const vec& in_data_lab)
{
	input_data(in_data, in_data_lab);
}


nb_model::~nb_model()
{
}


void nb_model::input_data(const mat& in_data, const vec& in_data_lab)
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


void nb_model::train()
{
	
	//class_num的确定
	int cnum = 0;
	for(int i = 0; i < label.size(); i++){
		if(!label_2_num.count(label[i])){
			label_2_num[label[i]] = cnum;
			cnum++;
		}
	}
	class_num = cnum;

	//数据分割, samp_data记录的仅仅是数据的位置索引，而不是数据本身
	mat samp_data;
	for(int i = 0; i < class_num; i++){
		vec temp;	
		for(int j = 0; j < samp_num; j++){
			if(label_2_num[label[j]] == i)
				temp.push_back(j);
		}
		samp_data.push_back(temp);
		temp.clear();
	}
	
	//概率计算
	//
	for(int i = 0; i < class_num; i++){
		vec temp_avg, temp_var;
		for(int j = 0; j < dim_num; j++){
			vec s_data; 
			for(int k = 0; k < samp_data[i].size(); k++){
				s_data.push_back(raw_data[samp_data[i][k]][j]);
			}
			double temp_a = average(s_data);
			temp_avg.push_back(temp_a);
			temp_var.push_back(variance(s_data, temp_a));
			s_data.clear();
		}
		mu.push_back(temp_avg);
		sigma.push_back(temp_var);
		temp_avg.clear();temp_var.clear();
		class_prob.push_back(1.0 * samp_data[i].size() / samp_num);
	}
	cout<<"The training is over!"<<endl;
	
}


vec nb_model::classification(const mat& t_data)
{
	vec resl;

	mat prob;
	for(int i = 0; i < t_data.size(); i++){
		vec temp_v;
		for(int j = 0; j < class_num; j++){
			double temp = class_prob[j];
			for(int k = 0; k < dim_num; k++){
				//cout << gaussian(t_data[i][k], mu[j][k], sigma[j][k]) << endl;
				temp = temp * gaussian(t_data[i][k], mu[j][k], sigma[j][k]);
			}
		temp_v.push_back(temp);
		}
		prob.push_back(temp_v);
		temp_v.clear();		
	}
	
	for(int i = 0; i < t_data.size(); i++){
		double max_prob = 0;
		int max_ind = -1;
		for(int j = 0; j < class_num; j++){
			if(prob[i][j] > max_prob){
				max_prob = prob[i][j];
				max_ind = j;
			}
		}

		map<double, int>::const_iterator iter;
		for (iter = label_2_num.begin(); iter != label_2_num.end(); iter++){
			if (iter->second == max_ind)
				resl.push_back(iter->first);
		}

	}

	return resl;
}



inline double average(const vec& s_data)
{
	double avg = 0.0;
	for(int i = 0; i < s_data.size(); i++)
		avg = avg + s_data[i];
	
	return avg/s_data.size();
}

inline double variance(const vec& s_data, const double avg)
{
	double var = 0.0;
	for(int i = 0; i < s_data.size(); i++){
		var = var + (s_data[i] - avg) * (s_data[i] - avg);
	}
	var = var / s_data.size();
	
	return sqrt(var);
}

//1维高斯模型概率,概率密度函数大于1是正常的，表示随机变量在这个值附件取值的概率比较大
inline double gaussian(const double x_d, const double mu_d, const double sigma_d)
{
	return 1.0/(sqrt(2*PI)*sigma_d)*exp(-(x_d-mu_d)*(x_d-mu_d)/2/sigma_d/sigma_d) + 1e-20;
}









