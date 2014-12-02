#include"../src/PCA/pca_head.h"
#include"../src/global.h"

int main()
{
	const int row_num=4,col_num=3;
	double data[row_num][col_num]={{3,5,7},{6,4,1},{7,7,9},{3,4,1}};
	mat test_data(row_num);

	for(int i=0;i<row_num;i++)
		test_data[i].resize(col_num);
	for(int i=0;i<row_num;i++)
		for(int j=0;j<col_num;j++)
			test_data[i][j]=data[i][j];

	PCA_model myPCA(test_data,row_num,col_num);

	myPCA.pca_solve_eig();
	myPCA.print();

	
	return 0;
}
