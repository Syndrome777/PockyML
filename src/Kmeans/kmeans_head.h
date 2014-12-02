
#ifndef _kmeans_head_h
#define _kmeans_head_h

#include"../global.h"

using namespace std;

class kmeans_clusters{
public:
	kmeans_clusters();
	kmeans_clusters(const mat& in_data);
	~kmeans_clusters();
	void input_data(const mat& in_data);
	void train(const int c_num);
	void display();

private:
	mat raw_data;//原始数据
	mat centroid;//质心
	vec label;//数据类别
	int cluster_num;//类别数
	int samp_num;//样本数
	int dim_num;//特征维数
	double get_variance();//得到方差
	void get_cluster_class();//得到分类标签
	void get_centroid();//得到质心
};


inline double variance(const vec& vec1, const vec& vec2);

#endif








