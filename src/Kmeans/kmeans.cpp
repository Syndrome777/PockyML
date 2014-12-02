#include"kmeans_head.h"


kmeans_clusters::kmeans_clusters()
{
}

kmeans_clusters::kmeans_clusters(const mat& in_data)
{
	input_data(in_data);
}

kmeans_clusters::~kmeans_clusters()
{
}

void kmeans_clusters::input_data(const mat& in_data)
{
	samp_num = in_data.size();
	dim_num = in_data[0].size();
	for(int i = 0; i < in_data.size(); i++){
		vec temp;
		for(int j = 0; j < in_data[i].size(); j++)
			temp.push_back(in_data[i][j]);
		raw_data.push_back(temp);
		label.push_back(-1);
	}
}

void kmeans_clusters::train(const int c_num)
{
	double delta_min = 1, oldvar = 0, newvar = -100;
	int iter_max = 100, iter = 1;
	cluster_num = c_num;
	if(samp_num < c_num){
		cout<<"ERROR:the num of sample is less than the num of class"<<endl;
		return;
	}
	for(int i = 0; i < cluster_num; i++){
		centroid.push_back(raw_data[i]);
	}
	get_cluster_class();
	newvar = get_variance();
	while(fabs(oldvar-newvar) > delta_min && iter <= iter_max){
		//display();
		oldvar = newvar;
		get_centroid();
		get_cluster_class();
		newvar = get_variance();
		iter++;
		cout<<"Delta:"<<fabs(oldvar-newvar)<<endl;
	}
	cout<<"Success!The iteration is: "<<iter<<endl;

}

void kmeans_clusters::get_centroid()
{
	mat cent(cluster_num);
	vec s_num(cluster_num);
	for(int i =0 ; i<cluster_num; i++)
		cent[i].resize(dim_num);
	for(int i = 0; i < samp_num; i++){
		for(int j = 0; j < dim_num; j++)
			cent[label[i]][j] = cent[label[i]][j] + raw_data[i][j];
		s_num[label[i]]++;
	}

	for(int i = 0; i < cluster_num; i++){
		for(int j = 0; j < dim_num; j++){
			if(s_num[i] != 0)
				cent[i][j] /= s_num[i];
			else
				cent[i][j] = centroid[i][j];
		}
		centroid[i] = cent[i];
	}
}

double kmeans_clusters::get_variance()
{
	double var_sum = 0;
	for(int i = 0; i < samp_num; i++)
		var_sum = var_sum + variance(raw_data[i],centroid[label[i]]);
	return var_sum;	
}

void kmeans_clusters::get_cluster_class()
{
	double delta;
	for(int i = 0; i < samp_num; i++){
		double d_min = 1e20;
		label[i] = 0;
		for(int j = 0; j < cluster_num; j++){
			delta = variance(raw_data[i],centroid[j]);
			if(delta < d_min){
				d_min = delta;
				label[i] = j;
			}
		}
	}
}


void kmeans_clusters::display()
{
	cout<<"The cluster is:"<<endl;
	for(int i = 0; i < samp_num; i++)
		cout<<label[i]<<endl;
	cout<<"The centriods are: "<<endl;
	for(int i = 0; i < cluster_num; i++){
		for(int j = 0; j < dim_num; j++)
			cout<<centroid[i][j]<<' ';
		cout<<endl;
	}
}


inline double variance(const vec& vec1, const vec& vec2)
{
	double var = 0;
	for(int i = 0; i < vec1.size(); i++)
		var = var + (vec1[i]-vec2[i]) * (vec1[i]-vec2[i]);
	return sqrt(var);
}





