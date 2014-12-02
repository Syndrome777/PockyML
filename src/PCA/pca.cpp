#include"pca_head.h"

PCA_model::PCA_model(){
}

PCA_model::~PCA_model(){
}

//template<T>
PCA_model::PCA_model(mat &data,int anum,int afea){	
	//i代表特征维数标签
	fea=afea;
	num=anum;

	mean.resize(fea);
	cov.resize(fea);
	for(int i=0;i<fea;i++)
		cov[i].resize(fea);

	for(int i=0;i<fea;i++){
		for(int j=0;j<num;j++)//j代表样本标签
			mean[i]+=data[j][i];
		mean[i]/=num;
	}
	for(int i=0;i<fea;i++)
		for(int j=0;j<=i;j++){
			for(int k=0;k<num;k++){
				cov[i][j]=cov[i][j]+(data[k][i]-mean[i])*(data[k][j]-mean[j]);
				cov[j][i]=cov[i][j];
			}
			cov[i][j]/=(num-1);
			if(i!=j)
				cov[j][i]/=(num-1);
		}

	eigenvalue.resize(fea);
	eigenvector.resize(fea);
	for(int i=0;i<fea;i++)
		eigenvector[i].resize(fea);
}


int PCA_model::pca_solve_eig()
{
	//const int aa=10;
	double *a,*v;

	a=new double[fea*fea];
	v=new double[fea*fea];


	for(int i=0;i<fea;i++)
		for(int j=0;j<fea;j++)
			a[i*fea+j]=cov[i][j];

	if(fea==0)
		cout<<"ERROR:NO data"<<endl;
	else
	{
		eejcb(a,fea,v,0.00001,10000);

		for(int i=0;i<fea;i++)
			for(int j=0;j<fea;j++){
				eigenvalue[i]=a[i*fea+i];
				eigenvector[i][j]=v[i*fea+j];
			}

		for(int i=0;i<fea;i++)
			for(int j=i+1;j<fea;j++){
				if(eigenvalue[i]<eigenvalue[j]){
					double tx;
					tx=eigenvalue[j];
					eigenvalue[j]=eigenvalue[i];
					eigenvalue[i]=tx;
					for(int k=0;k<fea;k++){
						tx=eigenvector[k][i];
						eigenvector[k][i]=eigenvector[k][j];
						eigenvector[k][j]=tx;
					}
				}
			}

	}
	if(a)
		delete[] a;
	if(v)
		delete[] v;

	return 0;
}


void PCA_model::print()
{
	cout<<"the cov is:"<<endl;
	for(int i=0;i<fea;i++){
		for(int j=0;j<fea;j++)
			cout<<setprecision(5)<<showpoint<<cov[i][j]<<' ';
		cout<<endl;
	}

	cout<<"the eigenvalue is:"<<endl;
	for(int i=0;i<fea;i++)
		cout<<setprecision(5)<<showpoint<<eigenvalue[i]<<' ';
	cout<<endl;

	cout<<"the eigenvector is:"<<endl;
	for(int i=0;i<fea;i++){
		for(int j=0;j<fea;j++)
			cout<<setprecision(5)<<showpoint<<eigenvector[i][j]<<' ';
		cout<<endl;
	}
}


//求实对称矩阵的特征值及特征向量的雅格比法
//利用雅格比(Jacobi)方法求实对称矩阵的全部特征值及特征向量
//返回值小于0表示超过迭代jt次仍未达到精度要求
//返回值大于0表示正常返回
//a-长度为n*n的数组，存放实对称矩阵，返回时对角线存放n个特征值
//n-矩阵的阶数
//v-长度为n*n的数组，返回特征向量(按列存储)
//eps-控制精度要求
//jt-整型变量，控制最大迭代次数
int eejcb(double a[],int n,double v[],double eps,int jt)
{ 

	int i,j,p,q,u,w,t,s,l;
	double fm,cn,sn,omega,x,y,d;
	l=1;
	for (i=0; i<=n-1; i++){ 
		v[i*n+i]=1.0;
		for (j=0; j<=n-1; j++){
			if (i!=j) {
				v[i*n+j]=0.0;
			}
		}
	}
	while (1){ 
		fm=0.0;
		for (i=0; i<=n-1; i++){
			for (j=0; j<=n-1; j++){ 
				d=fabs(a[i*n+j]);
				if ((i!=j)&&(d>fm)){ 
					fm=d; 
					p=i; 
					q=j;
				}
			}
		}
		if (fm<eps){
			return(1);
		}
		if (l>jt){
			return(-1);
		}
		l=l+1;
		u=p*n+q; 
		w=p*n+p; 
		t=q*n+p; 
		s=q*n+q;
		x=-a[u];
		y=(a[s]-a[w])/2.0;
		omega=x/sqrt(x*x+y*y);
		if (y<0.0){
			omega=-omega;
		}
		sn=1.0+sqrt(1.0-omega*omega);
		sn=omega/sqrt(2.0*sn);
		cn=sqrt(1.0-sn*sn);
		fm=a[w];
		a[w]=fm*cn*cn+a[s]*sn*sn+a[u]*omega;
		a[s]=fm*sn*sn+a[s]*cn*cn-a[u]*omega;
		a[u]=0.0;
		a[t]=0.0;
		for (j=0; j<=n-1; j++){
			if ((j!=p)&&(j!=q)){ 
				u=p*n+j;
				w=q*n+j;
				fm=a[u];
				a[u]=fm*cn+a[w]*sn;
				a[w]=-fm*sn+a[w]*cn;
			}
		}
		for (i=0; i<=n-1; i++){
			if ((i!=p)&&(i!=q)){ 
				u=i*n+p; 
				w=i*n+q;
				fm=a[u];
				a[u]=fm*cn+a[w]*sn;
				a[w]=-fm*sn+a[w]*cn;
			}
		}
		for (i=0; i<=n-1; i++){ 
			u=i*n+p; 
			w=i*n+q;
			fm=v[u];
			v[u]=fm*cn+v[w]*sn;
			v[w]=-fm*sn+v[w]*cn;
		}
	}
	return(1);
}
