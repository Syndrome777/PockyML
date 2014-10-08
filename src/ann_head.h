#ifndef _ANN_HEAD_H
#define _ANN_HEAD_H


#include"global.h"

using namespace std;


class ann_model{
	public:
		ann_model();
		ann_model(const mat& in_data, const vec& in_data_lab);
		~ann_model();
		void init(const int node_n);//初始化层间连接权值和学习速率
		void input_data(const mat& in_data, const vec& in_data_lab);
		void train(const int node_n);
		

	private:
		//数据参数
		mat raw_data;//原始数据
		vec label;//标签数据
		int samp_num;//样本数目
		int dim_num;//样本维度
		int class_num;//类的数目
	
		//模型参数
		double learn_rate;//学习速率
		int node_num;//隐层节点数
		int max_iter;//iteration,最大迭代次数
		
		mat W;//输入层和隐层间的连接权值，应为dim_num*node_num的矩阵
		vec W_a;//隐层阀值，长度node_num的向量
		mat V;//隐层和输出层间的连接权值，应为node_num*class_num的矩阵
		vec V_b;//输出层阀值，长度为class_num的向量

		double output_error(const vec& ans, const vec& res);//计算输出标签和真实标签的误差，为全局误差　
		vec prediction(const vec& in_data);//输出层结果预测，基于W和V矩阵
		vec correction();//参数修正，基于W,V误差修正

		inline double sigmoid(const double x);//activation function，激活函数
		inline double get_rand();//随机数[-1,1]

};



inline double multiplication(const vec& vec1, const vec& vec2);


/*

算法步骤：
(1）初始化，随机给定各连接权[w],[v]及阀值θi，rt。  
(2）由给定的输入输出模式对计算隐层、输出层各单元输出.    
(3）基于（2）中的输出与真实标签的误差，调整计算新的连接权及阀值. 
(4）返回第2步，反复训练直到网络设输出误差达到要求结束训练。 


*/





#endif // !






