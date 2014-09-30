#ifndef _KNN_HEAD_H_
#define _KNN_HEAD_H_


#include"global.h"

using namespace std;

class knn_model{
public:
	knn_model();//构造函数
	knn_model(const mat& in_data, const vec& in_data_lab);
	~knn_model();//析构函数

	void input_data(const mat& in_data, const vec& in_data_lab);//输入数据
	int classification(const vec& data_vec, const int k);//单样本分类
	vec classification(const mat& data_mat, const int k);//多样本分类
	

private:
	mat raw_data;//原始数据
	vec label;//原始标签
	int k_num;//k的数目
	int samp_num;//样本数目
	int dim_num;//数据维度数目
	
	
};


inline double Edistance(const vec& vec1, const vec& vec2);//Euclidean distance,欧式距离










#endif //!

