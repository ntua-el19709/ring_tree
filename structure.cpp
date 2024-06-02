#include <bits/stdc++.h>
#include <ctime>
#include "tree.h"
#include "mnist.h"

using namespace std;

int main(){
    srand(time(NULL));
    /*
    readmnist();
    JL_prepare();
    ifstream fin("JLmatrix.txt");
    JL_load(fin);
    JL_project();
    ofstream fout("MnistProjection.txt");
    JL_printprojection(fout);
    */
    vector<point*> dataset;
    ifstream fin("MnistProjection.txt");
    long double sq15=sqrt(15);
    for(int i=0;i<60000;i++){
        long double vdim[15];
        for(int j=0;j<15;j++){
            int t;
            fin>>t;
            vdim[j]=(long double)(t)/sq15;
        }
        point *a=new point(15,vdim);
        dataset.push_back(a);
    }


    int sample=1000;
    long double edist=0,mindist[3000];
    for(int i=0;i<3000;i++){
        long double tdist=dist(dataset[i],dataset[3000]);
        for(int j=0;j<3000;j++){
            if(i==j)continue;
            tdist=min(tdist,dist(dataset[i],dataset[j]));
        }
        edist+=tdist;
        mindist[i]=tdist;
    }
    sort(mindist,mindist+3000);
    edist/=3000.0;
    cout<<"Mean min dist: "<<setprecision(20)<<edist<<endl;
    cout<<"20 quantile: "<<mindist[599]<<endl;
    tree *root=new tree(15,mindist[599]);

    for(int i=0;i<sample;i++){
        root->add(dataset[i]);
    }
    root->findseploc();
    root->print();
    //root->build_tree();
    //root->printtofile("tree_20quant_sam1000.txt");


/*
    long double adim[2]={3,2},bdim[2]={5,6},cdim[2]={1,4},ddim[2]={-1,-1},edim[2]={-2,6},fdim[2]={3,5},gdim[2]={5,3},hdim[2]={2,0},idim[2]={4,0},jdim[2]={1,-2},kdim[2]={-1,2},ldim[2]={4,-2};
    point *a=new point(2,adim);
    point *b=new point(2,bdim);
    point *c=new point(2,cdim);
    point *d=new point(2,ddim);
    point *e=new point(2,edim);
    point *f=new point(2,fdim);
    point *g=new point(2,gdim);
    point *h=new point(2,hdim);
    point *i=new point(2,idim);
    point *j=new point(2,jdim);
    point *k=new point(2,kdim);
    point *l=new point(2,ldim);
    //point *a=new point(3,{2,2,2});
    //point *b=new point(3,{-2,0,3});
    //point *c=new point(3,{4,0,4});
    //point *d=new point(3,{3,-2,1});
    vector<point*> firsttest;
    firsttest.push_back(a);
    firsttest.push_back(b);
    firsttest.push_back(c);
    //firsttest.push_back(d);
    int ooi[3];
    ooi[0]=0;
    ooi[1]=1;
    ooi[2]=2;
    //ooi[3]=0;
    //separator *sep=new separator(2,firsttest,ooi,10);
    //sep->print();
    //cout<<endl<<endl;

    tree *root=new tree("treestructure.txt");
    /*
    root->add(a);
    root->add(b);
    root->add(c);
    root->add(d);
    root->add(e);
    root->add(f);
    root->add(g);
    root->add(h);
    root->add(i);
    root->add(j);
    root->add(k);
    root->add(l);
    root->build_tree();

    root->print();
    //root->printtofile("treestructure.txt");
    delete a,b;
    */
}
