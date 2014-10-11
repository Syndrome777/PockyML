
#ifndef _NB_HEAD_H_
#define _NB_HEAD_H_


#include"global.h"

using namespace std;

class nb_model{
	public:
		nb_model();
		nb_model(const mat& in_data, const vec& in_data_lab);
		~nb_model();
		void input_data(const mat& in_data, const vec& in_data_lab);
		void train();//train the model
		vec classifaction(const mat& t_data);//using the model to classify

	private:
		mat raw_data;
		vec label;
		int samp_num;
		int dim_num;
		int class_num;
}







#endif//!


