#include"../src/Kmeans/kmeans_head.h"
#include"../src/global.h"
#include<fstream>


int main()
{
	kmeans_clusters mykmean;

	mat data;
	ifstream file("test_data/test_data_cluster.txt");
	//ifstream file("C:\\Users\\Hua\\Documents\\GitHub\\PockyML\\src\\test_data.txt");
	for (int i = 0; i < 10; i++){
		vec temp;
		double a;
		for (int j = 0; j < 3; j++){
			file >> a;
			temp.push_back(a);
		}
		data.push_back(temp);
		temp.clear();
	}
	cout << "success to input data" << endl;
	cout << data[0][0] << endl;

	mykmean.input_data(data);
	mykmean.train(3);
	mykmean.display();

	return 0;
}



/*
test data:

1 2 3
2 3 4
2 7 9 
6 8 9
100 200 100
1 2 1
4 5 2
11 23 10
2 34 12
44 31 11

cluster:
3

result:
label =

     1
     1
     1
     1
     2
     1
     1
     3
     3
     3


Centriod =

    2.6667    4.5000    4.6667
  100.0000  200.0000  100.0000
   19.0000   29.3333   11.0000
*/



	



