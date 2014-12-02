#include"../src/NB/nb_head.h"
#include"../src/global.h"
#include <fstream>


int main()
{
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

	nb_model myNB(data,lab);
	myNB.train();

	cout << "the labels of the test data" << endl;
	vec test_lab;
	int rig = 0;
	test_lab = myNB.classification(data);
	for (int i = 0; i < test_lab.size(); i++){
		cout << i+1 << " " <<test_lab[i] << endl;
		if (test_lab[i] == lab[i])
			rig++;
	}
	cout << "Corrate rate is: " << 1.0 * rig / test_lab.size() << endl;

	//system("pause");
	return 0;
}

