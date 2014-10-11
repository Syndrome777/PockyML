
#ifndef _NB_HEAD_H_
#define _NB_HEAD_H_


#include"global.h"
//#include"../../3rd/Eigen/LU"

using namespace std;
//using Eigen::MatrixXd;

class nb_model{
	public:
		nb_model();
		nb_model(const mat& in_data, const vec& in_data_lab);
		~nb_model();
		void input_data(const mat& in_data, const vec& in_data_lab);
		void train();//train the model
		vec classification(const mat& t_data);//using the model to classify

	private:
		mat raw_data;
		vec label;
		int samp_num;
		int dim_num;
		int class_num;
		map<double, int> label_2_num;//label to number,class_num的确定
		//model's parameters
		mat mu;//
		mat sigma;//
		vec class_prob;//类别在训练样本中的概率

}


inline double gaussian(const double x_d, const double mu_d, const double sigma_d);

inline double variance(const vec& s_data, const double avg);

inline double average(const vec& s_data);

/*
 
	P(yi/x) = [p(x/yi) * p(yi)] / P(x);
	P(x/yi) = P(yi) * 求积[P(aj/yi)];//基于统计独立假设，aj为x的属性ß
	对于连续数据而言，假定数据服从高斯（正态）分布 
	P(ak/yi) = g(ak, nk, delteij); 
	求解高斯分布，获得概率
 
 
 */




#endif//!


