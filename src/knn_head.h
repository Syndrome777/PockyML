#ifndef _KNN_HEAD_H_
#define _KNN_HEAD_H_


#include"global.h"


class knn_model{
public:
	knn_model();
	knn_model(const mat& in_data, const vec& in_data_lab);
	~knn_model();

	void input_data(const mat& in_data, const vec& in_data_lab);
	int classification(const vec& data_vec, const int k);
	vec clssification(const mat& data_mat, const int k);
	

private:
	mat raw_data;//原始数据
	vec label;//原始标签
	int k_num;//k的数目
	int samp_num;//样本数目
	int dim_num;//数据维度数目
	
	
}


inline double distance(const vec& vec1, const vec& vec2);//Euclidean distance,欧式距离










#endif //!

