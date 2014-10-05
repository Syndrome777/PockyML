#ifndef _ANN_HEAD_H
#define _ANN_HEAD_H


#include"global.h"

using namespace std;


class ann_model{
	public:
		ann_model();
		ann_model(const mat& in_data);
		~ann_model();
		void input_data(const mat& in_data);
		void train();
		

	private:
		mat raw_data;//原始数据
		int samp_num;//样本数目
		int dim_num;//样本维度

}




#endif // !






