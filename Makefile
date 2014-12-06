# -std=c++11

VPATH=src:src/ANN:src/NB:src/Kmeans:src/KNN:src/PCA:src/LR:test

CC=g++

all:ann_test nb_test kmeans_test knn_test pca_test lr_test
.PHONY:all

#echo "compiling ann"
ann.o:ann.cpp ann_head.h global.h
	${CC} -c -std=c++11 src/ANN/ann.cpp -o ann.o
ann_test:ann_test.cpp ann.o
	${CC} -std=c++11 ann.o test/ann_test.cpp -o ann_test

#echo "compiling nb"
nb.o:nb.cpp nb_head.h global.h
	${CC} -c -std=c++11 src/NB/nb.cpp -o nb.o
nb_test:nb_test.cpp nb.o
	${CC} -std=c++11 nb.o test/nb_test.cpp -o nb_test

#echo "compiling kmeans"
kmeans.o:kmeans.cpp kmeans_head.h global.h
	${CC} -c -std=c++11 src/Kmeans/kmeans.cpp -o kmeans.o
kmeans_test:kmeans_test.cpp kmeans.o
	${CC} -std=c++11 kmeans.o test/kmeans_test.cpp -o kmeans_test

#echo "compiling knn"
knn.o:knn.cpp knn_head.h global.h
	${CC} -c -std=c++11 src/KNN/knn.cpp -o knn.o
knn_test:knn_test.cpp knn.o
	${CC} -std=c++11 knn.o test/knn_test.cpp -o knn_test

#echo "compiling pca"
pca.o:pca.cpp pca_head.h global.h
	${CC} -c -std=c++11 src/PCA/pca.cpp -o pca.o
pca_test:pca_test.cpp pca.o
	${CC} -std=c++11 pca.o test/pca_test.cpp -o pca_test

#echo "compiling lr"
lr.o:lr.cpp lr_head.h global.h
	${CC} -c -std=c++11 src/LR/lr.cpp -o lr.o
lr_test:lr_test.cpp lr.o
	${CC} -std=c++11 lr.o test/lr_test.cpp -o lr_test



.PHONY:clean
clean:
	-rm *.o ann_test nb_test kmeans_test knn_test pca_test lr_test



