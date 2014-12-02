#include"../src/KNN/knn_head.h"
#include"../src/global.h"
#include<fstream>


int main()
{
	knn_model myknn;
	mat data;
	vec lab;
	ifstream file("test_data/test_data.txt");
	//ifstream file("C:\\Users\\Hua\\Documents\\GitHub\\PockyML\\src\\test_data.txt");
	for (int i = 0; i < 150; i++){
		vec temp;
		double a;
		for (int j = 0; j < 4; j++){
			file >> a;
			temp.push_back(a);
		}
		file >> a;
		lab.push_back(a);
		data.push_back(temp);
		temp.clear();
	}
	cout << "success to input data" << endl;

	myknn.input_data(data, lab);

	vec result = myknn.classification(data,3);
	int acc;
	cout << "result : " <<endl;
	for(int i = 0; i < result.size(); i++){
		cout << i << "'s label is " << result[i] << endl;
		if(result[i] == lab[i])
			acc++;
	}
	cout << "The accuracy is" << 1.0*acc/result.size() << endl;
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


