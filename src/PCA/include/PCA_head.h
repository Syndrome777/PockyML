//PCA算法头文件
#ifndef _PCA_head_H_  
#define _PCA_head_H_

#include<iostream>
#include<vector>
#include<math.h>
#include<iomanip>

//#include"PCA_head.h"

using namespace std;


class PCA_model{
	public:
		vector<vector<double>> eigenvector;//特征向量矩阵
		vector<double> eigenvalue;//特征值

		PCA_model();
		PCA_model(vector<vector<double>> data,int anum,int afea);
		~PCA_model();
		void print();
		int pca_solve_eig();

	private:
		int num;//样本数
		int fea;//特征维数
		vector<vector<double>> cov;//协方差矩阵
		vector<double> mean;//平均值		
};


//约化对称矩阵为三对角对称矩阵
//利用Householder变换将n阶实对称矩阵约化为对称三对角矩阵
//a-长度为n*n的数组，存放n阶实对称矩阵
//n-矩阵的阶数
//q-长度为n*n的数组，返回时存放Householder变换矩阵
//b-长度为n的数组，返回时存放三对角阵的主对角线元素
//c-长度为n的数组，返回时前n-1个元素存放次对角线元素
//void eastrq(double a[],int n,double q[],double b[],double c[]);

//求实对称三对角对称矩阵的全部特征值及特征向量
//利用变型QR方法计算实对称三对角矩阵全部特征值及特征向量
//n-矩阵的阶数
//b-长度为n的数组，返回时存放三对角阵的主对角线元素
//c-长度为n的数组，返回时前n-1个元素存放次对角线元素
//q-长度为n*n的数组，若存放单位矩阵，则返回实对称三对角矩阵的特征向量组
//  若存放Householder变换矩阵，则返回实对称矩阵A的特征向量组
//a-长度为n*n的数组，存放n阶实对称矩阵
//int ebstq(int n,double b[],double c[],double q[],double eps,int l);

//约化实矩阵为赫申伯格(Hessen berg)矩阵
//利用初等相似变换将n阶实矩阵约化为上H矩阵
//a-长度为n*n的数组，存放n阶实矩阵,返回时存放上H矩阵
//n-矩阵的阶数
//void echbg(double a[],int n);

//void echbg(mat a,int n);

//求赫申伯格(Hessen berg)矩阵的全部特征值
//返回值小于0表示超过迭代jt次仍未达到精度要求
//返回值大于0表示正常返回
//利用带原点位移的双重步QR方法求上H矩阵的全部特征值
//a-长度为n*n的数组，存放上H矩阵
//n-矩阵的阶数
//u-长度为n的数组，返回n个特征值
//v-长度为n*n的数组，返回n个特征值的特征向量
//eps-控制精度要求
//jt-整型变量，控制最大迭代次数
//int edqr(double a[],int n,double u[],double v[],double eps,int jt);


//求实对称矩阵的特征值及特征向量的雅格比法
//利用雅格比(Jacobi)方法求实对称矩阵的全部特征值及特征向量
//返回值小于0表示超过迭代jt次仍未达到精度要求
//返回值大于0表示正常返回
//a-长度为n*n的数组，存放实对称矩阵，返回时对角线存放n个特征值
//n-矩阵的阶数
//v-长度为n*n的数组，返回特征向量(按列存储)
//eps-控制精度要求
//jt-整型变量，控制最大迭代次数
int eejcb(double a[],int n,double v[],double eps,int jt);



#endif