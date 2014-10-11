#ifndef _ANN_HEAD_H_
#define _ANN_HEAD_H_


#include"global.h"

using namespace std;


class ann_model{
	public:
		ann_model();
		ann_model(const mat& in_data, const vec& in_data_lab);
		~ann_model();
		void init(const int node_n);//初始化层间连接权值和学习速率
		void input_data(const mat& in_data, const vec& in_data_lab);
		void train();//train for the model and parameters
		vec classifcation(const mat& t_data);//预测
		void parameter_setting(const double learn_r, const int max_i, const double min_e);//parameter setting,the num of hidden nodes, the rate of learning, the max iteration, the min of error
		

	private:
		//数据参数
		mat raw_data;//原始数据
		vec label;//标签数据
		int samp_num;//样本数目
		int dim_num;//样本维度
		int class_num;//类的数目
		map<double,int> label_2_num;//标签转数字，确定class_num，防止label的中断，如label为1，2，4。。。
		
		//模型参数
		double learn_rate;//学习速率
		int node_num;//隐层节点数
		int max_iter;//iteration,最大迭代次数
		double min_error;//最小前后误差差，err_all-err_pre
		mat result_mat;//结果输出矩阵，并非真实标签，samp_num*class_num
		mat answer_mat;//真实标签矩阵,samp_num*class_num
		//vec mid;//隐藏层数据
		
		mat W;//输入层和隐层间的连接权值，应为dim_num*node_num的矩阵
		vec W_a;//隐层阀值，长度node_num的向量
		mat V;//隐层和输出层间的连接权值，应为node_num*class_num的矩阵
		vec V_b;//输出层阀值，长度为class_num的向量

		
		double error_all(const mat& res);//输入为模型的输出标签，sample_num * class_num，并没用转换为真实标签
		double error_one(const vec& ans1, const vec& res1);//计算输出标签和真实标签的误差，为全局误差　
		vec prediction(const vec& in_data, vec& mid);//输出层结果预测，基于W和V矩阵
		void correction(const vec& in_d, const vec& mid_d, const vec& out_d, const vec& ans_d);//参数修正，基于W,V误差修正

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






