----------
Welcome to PockyML!
===================

This project is named Pocky Machine Learning. It's a lightweight open source C++ machine learning library.  
I'm a novice in ML, but I think I love it. So I will try my best to write this tool. Meanwhile the Chocolate bars of Pocky is so delicious.


Algorithm 
---------

#### 1.  K-means
How to use it
```c++
	kmeans_clusters mykmean;
	mykmean.input_data(test_data);
	mykmean.train(3);
	mykmean.display();
```

#### 2.  GMM (Gaussian Mixture Model, Unfinished)
#### 3.  KNN (K-Nearest Neighbor)
How to use it
```c++
	knn_model myknn;
	myknn.input_data(test_data, label);
	//k=3
	result = myknn.classification(try_data,3);
```

#### 4.  SVM (Suport Vector Machine, based on LibSVM)
#### 5.  ANN (Artifical Neural Network)
How to use it
```c++
	ann_model myANN(data,lab);
	//set the num of hidden nodes
	myANN.init(10);
	//set other parameters, learning_rate, iteration_times, 
	myANN.parameter_setting(0.02, 80000, 0.000000001);
	myANN.train();
	test_lab = myANN.classification(data);
```

#### 6.  PCA (Principal Component Analysis)
How to use it
```c++
	PCA_model myPCA(test_data,row_num,col_num);

	myPCA.pca_solve_eig();
	myPCA.print();
```

#### 7.  NB (Naive Bayesian)
How to use it
```c++
	nb_model myNB(data,lab);
	myNB.train();
	test_lab = myNB.classification(data);
```

#### 8.  LR (Logistic Regression, Unfinished)
#### 9.  C4.5 (Deccision Tree, Unfinished)
#### 10. Adaboost (Baesd on C4.5 Unfinished)


Author 
------

Issac (issac.sacrifice@gmail.com,from Zhejiang University)
