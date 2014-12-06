
#ifndef _SVM_HEAD_H_
#define _SVM_HEAD_H_

#include"../src/global.h"
#include"libsvm_svm.h"

using namespace std;


class SVM_MODEL{
	public:
		SVM_MODEL();
		SVM_MODEL(const mat& in_data, const vec& in_data_lab);
		~SVM_MODEL();

		void init();
		void init(const string& kernel_t);
		bool input_data(const mat& in_data, const vec& in_data_lab);
		bool train();
		vec prediction(const mat& in_data);

	private:
		//data parameter
		int samp_num;
		int dim_num;
		mat raw_data;
		vec label;
		//model parameter
		string kernel;

		struct svm_model *model;
		struct svm_parameter param;
		struct svm_problem prob;
	
};




#endif //!



