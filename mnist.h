#include <bits/stdc++.h>
#include <ctime>
//#include <Eigen/Sparse>
#include <Eigen/Dense>
using namespace std;

using Eigen::MatrixXi;
//using Eigen::SparseMatrix;

MatrixXi Mnist(784,60000);
MatrixXi JLP(15,784);
MatrixXi Projection(15,60000);
//SparseMatrix<double> Mnist(784,60000);
short int labels[60000];

void readmnist(){
    FILE *fp;
    fp = fopen("mnist_train.csv","r");

    char t=',';
    while(t!='\n'){
        fscanf(fp,"%c",&t);
    }
    for(int i=0;i<60000;i++){
        fscanf(fp,"%d,",&labels[i]);
        for(int j=0;j<784;j++){
            int a;
            fscanf(fp,"%d%c",&a,&t);
            Mnist(j,i)=a;
            //Mnist.insert(j,i)=a;
        }
    }
    //Mnist.makeCompressed();
    fclose(fp);
}
void JL_load(istream &in){
    for(int i=0;i<15;i++){
        for(int j=0;j<784;j++){
            short t;
            in>>t;
            JLP(i,j)=t;
        }
    }
}
void JL_prepare(){
    for(int i=0;i<15;i++){
        for(int j=0;j<784;j++){
            short t=2*(rand()%2)-1;
            JLP(i,j)=t;
        }
    }
    //MatrixXi Projection = JLP * Mnist;
}
void JL_printmatrix(ostream &out=cout){
    for(int i=0;i<15;i++){
        for(int j=0;j<784;j++){
            out<<fixed<<setw(3)<<JLP(i,j);
        }
        out<<endl;
    }
}
void JL_project(){
    Projection=JLP*Mnist;
}
void JL_printprojection(ostream &out=cout){//column by column
    for(int i=0;i<60000;i++){
        for(int j=0;j<15;j++){
            int t=Projection(j,i);
            out<<Projection(j,i)<<" ";
        }
        out<<endl;
    }
}
