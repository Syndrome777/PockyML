#include"knn_head.h"


knn_model::knn_model()
{
}

knn_model::knn_model(const mat& in_data, const vec& in_data_lab)
{
	input_data(in_data, in_data_lab);	
}

knn_model::~knn_model()
{
}

void knn_model::input_data(const mat& in_data, const vec& in_data_lab)
{
	samp_num = in_data.size();
	dim_num = in_data[0].size();
	for(int i = 0; i < in_data.size(); i++){
		vec temp;
		for(int j = 0; j < in_data.size(); i++)
			temp.push_back(in_data[i][j]);
		raw_data.push_back(temp);
		label.push_back(in_data_lab[i]);
	}
}



int knn_model::classification(const vec& data_vec, const int k)
{
	vec dis, dis_copy; 
	vec resl_lab;
	int resl = 0;
	
	for(int i = 0; i < samp_num; i++){
		dis.push_back(1);
		Edistance(data_vec, raw_data[i]);
		
	}
	
	dis_copy = dis;
	sort(dis.begin(),dis.end());

	for(int i = 0; i < k; i++){
		for(int j = 0; j < samp_num; j++)
			if(dis_copy[j] == dis[i]){
				resl_lab.push_back(label[j]);
				dis_copy[j] = 0;
			}
	}
	
	map<int,int> lab_map;
	for(int i = 0; i < k; i++)
		lab_map[resl_lab[i]] = 0;
	for(int i = 0; i< k; i++)
		lab_map[resl_lab[i]]++;
	
	map<int,int>::iterator it;
	int count_num = 0;
	
	for (map<int, int>::iterator it = lab_map.begin(); it != lab_map.end(); it++){
		if(count_num < it->second){
			resl = it->first;
			count_num = it->second;
		}
	}
	
	return resl;
}



vec knn_model::classification(const mat& data_mat, const int k)
{
	vec resl;
	for(int i = 0; i < data_mat.size(); i++){
		resl.push_back(classification(data_mat[i],k));
	}
	return resl;
}




inline double Edistance(const vec& vec1, const vec& vec2)
{
	double var = 0;
	for(int i = 0; i < vec1.size(); i++)
		var = var + (vec1[i]-vec2[i]) * (vec1[i]-vec2[i]);
	return sqrt(var);
}






int main()
{


	
	
	
	return 0;
}






