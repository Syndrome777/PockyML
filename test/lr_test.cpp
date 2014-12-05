#include"../src/LR/lr_head.h"
#include"../src/global.h"
#include<fstream>



int main()
{
	mat data;
	vec lab;

	int samp = 10;
	int dim = 4;

	ifstream file("/test_data/test_data.txt");
	for(int i = 0; i < samp; i++){
		vec temp;
		double a;
		for(int j = 0; j < dim; j++){
			file >> a;
			temp.push_back(a);
		}
		file >> a;
		lab.push_back(a);
		data.push_back(temp);
		temp.clear();
	}
	cout << "success to input data" <<endl;

	lr_model myLR(data,lab);

	myLR.init();
	myLR.train();

	vec reg;
	reg = myLR.prediction(data);
	
	cout << "The prediction of regression is :" << endl;
	for(int i = 0 ; i < reg.size(); i++){
		cout << lab[i] << "  " << reg[i] << endl;
	}

	return 0;
}





