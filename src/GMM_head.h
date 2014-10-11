#ifndef _GMM_HEAD_H_
#define _GMM_HEAD_H_


#include"global.h"

using namespace std;

typedef struct node{
	mat sigam;
	vec miu;
	double pi;
}gmm_node;


class GMM_model{
public:
	GMM_model();
	GMM_model(const mat& in_data);
	~GMM_model();
	void input_data(const mat& in_data);
	void train(const int g_num);
	double probability(const vec& sample);
	void display();

private:
	vector<gmm_node> para;//高斯模型参数
	mat raw_data;//原始数据
	int gauss_num;//高斯数
	int samp_num;//样本数
	int dim_num;//特征维数
	mat gama;//概率矩阵：每个点对应每个高斯分布的概率
	double get_prob(const int i, const int k);//获取整体后验概率，E步骤
	void adjust_para();//参数调整，M步骤
	
};




inline double gaussian(const vec& mu, const mat& sigma);

#endif // !










