#include"../src/ANN/ann_head.h"
#include"../src/global.h"
#include <fstream>


int main()
{
	mat data;
	vec lab;
	ifstream file("../test_data/test_data.txt");
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

	ann_model myANN(data,lab);
	//set the num of hidden nodes
	myANN.init(10);
	//set other parameters
	myANN.parameter_setting(0.02, 80000, 0.000000001);
	myANN.train();

	cout << "the labels of the test data" << endl;
	vec test_lab;
	int rig = 0;
	test_lab = myANN.classification(data);
	for (int i = 0; i < test_lab.size(); i++)
		if (test_lab[i] == lab[i])
			rig++;
	cout << "Corrate rate is: " << 1.0 * rig / test_lab.size() << endl;

	return 0;
}
