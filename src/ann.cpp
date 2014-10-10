#include"ann_head.h"


ann_model::ann_model()
{
}

ann_model::ann_model(const mat& in_data, const vec& in_data_lab)
{
	input_data(in_data, in_data_lab);
}

ann_model::~ann_model()
{
}


void ann_model::input_data(const mat& in_data, const vec& in_data_lab)
{
	samp_num = in_data.size();
	dim_num = in_data[0].size();
	for(int i = 0; i < in_data.size(); i++){
		vec temp;
		for(int j = 0; j < in_data[0].size(); j++)
			temp.push_back(in_data[i][j]);
		raw_data.push_back(temp);
		label.push_back(in_data_lab[i]);
	}
}


void ann_model::init(const int node_n)
{
	node_num = node_n;
	max_iter = 1000;
	min_error = 0.00001;
	
	//class_num的确定
	int cnum = 0;
	for(int i = 0; i < label.size(); i++){
		if(!label_2_num[label[i]]){
			label_2_num[label[i]] = cnum;
			cnum++;
		}
	}
	class_num = cnum;

	//W,W_a,V,V_b的确定
	for(int i = 0; i < dim_num; i++ ){
		vec temp;
		for(int j = 0; j < node_num; j++ )
			temp.push_back(get_rand());
		W.push_back(temp);
		temp.clear();
	}
	for(int i = 0; i < node_num; i++)
		W_a.push_back(get_rand());

	for(int i = 0; i < node_num; i++ ){
		vec temp;
		for(int j = 0; j < class_num; j++ )
			temp.push_back(get_rand());
		V.push_back(temp);
		temp.clear();
	}
	for(int i = 0; i < class_num; i++)
		V_b.push_back(get_rand());

	//answer_mat的确定
	for(int i = 0; i < samp_num; i++){
		vec ans1;
		for(int j = 0; j < class_num; j++){
			if(j != label_2_num[label[i]])
				ans1.push_back(0);
			else
				ans1.push_back(1);
		}
		answer_mat.push_back(ans1);
		ans1.clear();
	}

	//result_mat的初始化
	for(int i = 0; i < samp_num; i++){
		vec res1;
		for(int j = 0; j < class_num; j++){
			res1.push_back(0);
		}
		result_mat.push_back(res1);
		res1.clear();
	}

}



void ann_model::train()
{
	//1.遍历每一个样本
	//2.修正参数
	//3.计算总误差，并判断
	//4.回到1
	int iter = 1;
	double err_all;
	while(!(err_all < min_error || iter > max_iter)){
		iter++;
		for(int i = 0; i < samp_num; i++){
			vec temp_in, temp_mid, temp_out, temp_ans;
			temp_in = raw_data[i];
			temp_out = prediction(temp_in, temp_mid);
			//输出结果矩阵的更新	
			result_mat[i] = temp_out;
			correction(temp_in, temp_mid, temp_out, temp_ans);	
			temp_in.clear();temp_mid.clear();temp_out.clear();temp_out.clear();
		}
		err_all = error_all(result_mat);

	}
}


vec ann_model::prediction(const vec& in_data, vec& mid)
{
	//隐层节点数据
	vec temp;
	vec resl;
	double mid_res;

	//输入层到隐层的映射，通过sigmoid函数
	for(int i = 0; i < node_num; i++){
		for(int j = 0; j < dim_num; j++)
			temp.push_back(W[j][i]);
		mid_res = multiplication(in_data, temp)- W_a[i];
		mid.push_back(sigmoid(mid_res));
		temp.clear();
	}

	//隐层到输出层的映射，通过sigmoid函数
	for(int i = 0; i < class_num; i++){
		for(int j = 0; j < node_num; j++)
			temp.push_back(V[j][i]);
		mid_res = multiplication(mid, temp) - V_b[i];
		resl.push_back(sigmoid(mid_res));
		temp.clear();
	}

	return resl;
}


void ann_model::correction(const vec& in_d, const vec& mid_d, const vec& out_d, const vec& ans_d)
{

	//输出层参数调整
	//W(j,k) = n*Q*y = n * (d(k) - o(k)) * o(k) * (1 - o(k)) * y(j)
	//其中d为真实标签，o为模型输出标签序列，y为输出层输入序列
	//n表示学习速率，为(0,1)

	mat delta_V;	
	vec delta_V_b;
	vec Q;//定义为输出层反向误差信号,长度为class_num
	//calculate for delta
	for(int i = 0; i < class_num; i++){
		double temp = (ans_d[i] - out_d[i]) * out_d[i] * (1 - out_d[i]);
		Q.push_back(temp);
		delta_V_b.push_back(learn_rate * temp);
	}
	for(int i = 0; i < node_num; i++){
		vec temp;
		for(int j = 0; j < class_num; j++){
			temp.push_back(learn_rate * Q[j] * mid_d[i]);
		}
		delta_V.push_back(temp);
		temp.clear();
	}
	//new V and V_b
	for(int i = 0; i < node_num; i++)
		for(int j = 0; j < class_num; j++){
			V[i][j] = V[i][j] + delta_V[i][j];
		}
	for(int i = 0; i < class_num; i++)
		V_b[i] = V_b[i] + delta_V_b[i];


	//隐含层参数调整
	//w(i,j) = n*Q*y = n * (sum(Q(k) *W(j,k))) * y(j) * (1-y(j)) * x(i)
	mat delta_W;
	vec delta_W_a;
	vec Q2;//隐含层反向误差信号，长度为node_num
	//calculate for delta
	for(int i = 0; i < node_num ;i++){
		double temp = 0;
		for(int j = 0; j < class_num; j++){
			temp = temp + Q[j] * V[i][j];
		}
		temp = temp * mid_d[i] * (1 - mid_d[i]);
		Q2.push_back(temp);
		delta_W_a.push_back(learn_rate * temp);
	}
	for(int i = 0; i < dim_num; i++){
		vec temp;
		for(int j = 0; j < node_num; j++){
			temp.push_back(learn_rate * Q2[j] * in_d[i]);
		}
		delta_W.push_back(temp);
		temp.clear();
	}
	//new W and W_a;
	for(int i = 0; i < dim_num; i++)
		for(int j = 0; j < node_num; j++){
			W[i][j] = W[i][j] + delta_W[i][j];
		}
	for(int i = 0; i < node_num; i++)
		W_a[i] = W_a[i] + delta_W_a[i];


}



double ann_model::error_all(const mat& res)
{
	double Eor = 0;
	for(int i = 0; i < samp_num; i++ ){
		Eor = Eor + error_one(answer_mat[i],res[i]);
	}
	return Eor;
}


double ann_model::error_one(const vec& ans, const vec& res)
{
	double Eor = 0.0;
	for(int i = 0; i < samp_num; i++){
		Eor = Eor + 1.0 * (ans[i] - res[i]) * (ans[i] - res[i]);
	}
	Eor = Eor / (2 * class_num);
	return Eor;
}



inline double ann_model::sigmoid(const double x)
{
	return 1.0/(1+exp(-1.0*x));
}


inline double ann_model::get_rand()
{
	return 2.0*rand()/RAND_MAX - 1.0;
}



inline double multiplication(const vec& vec1, const vec& vec2)
{
	double res = 0;
	for(int i = 0; i < vec1.size(); i++){
		res = res + vec1[i] * vec2[i];
	}
	return res;
}







