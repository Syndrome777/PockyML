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
		for(int j = 0; j < in_data[0].size(); j++)
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
		dis.push_back(Edistance(data_vec, raw_data[i]));
		
	}
	
	dis_copy = dis;
	sort(dis.begin(),dis.end());

	for(int i = 0; i < k; i++){
		for(int j = 0; j < samp_num; j++)
			if(dis_copy[j] == dis[i]){
				resl_lab.push_back(label[j]);
				dis_copy[j] = 0;
				break;
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
	knn_model myknn;
	double input;
	mat test_data(10);
	vec label;
	vec try_data;
	mat try_data2;

	for (int i = 0; i < 10; i++)
		test_data[i].resize(3);
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < 3; j++){
			cin >> input;
			test_data[i][j] = input;
		}
		cin >> input;
		label.push_back(input);
	}

	myknn.input_data(test_data, label);

	try_data.push_back(1);
	try_data.push_back(2);
	try_data.push_back(1);

	int result = myknn.classification(try_data,3);
	cout << "try_data result : " << result << endl;

	try_data2.push_back(try_data);
	try_data[0] = 30;
	try_data[0] = 40;
	try_data[0] = 50;
	try_data2.push_back(try_data);

	vec result2 = myknn.classification(try_data2, 3);
	cout << "try_data2 result : " << result2[0] << "   " << result2[1] << endl;

	getchar(); getchar();
	return 0;
}


/*
test data:

1 2 3 3
2 3 4 1
2 7 9 1
6 8 9 1
100 200 100 4
1 2 1 3
4 5 2 1
11 23 10 4
2 34 12 4
44 31 11 4

k:
3


result:
try_data result : 3
try_data result2 : 3   4

*/



