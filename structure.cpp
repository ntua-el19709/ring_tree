#include <bits/stdc++.h>
#include "tree.h"

using namespace std;

int main(){
    long double adim[2]={0,0},bdim[2]={0,2},cdim[2]={2,0},ddim[2]={2,2},edim[2]={4,3};
    point *a=new point(2,adim);
    point *b=new point(2,bdim);
    point *c=new point(2,cdim);
    point *d=new point(2,ddim);
    point *e=new point(2,edim);
    //point *a=new point(3,{2,2,2});
    //point *b=new point(3,{-2,0,3});
    //point *c=new point(3,{4,0,4});
    //point *d=new point(3,{3,-2,1});
    vector<point*> firsttest;
    firsttest.push_back(b);
    firsttest.push_back(c);
    firsttest.push_back(e);
    //firsttest.push_back(d);
    int ooi[3];
    ooi[0]=2;
    ooi[1]=2;
    ooi[2]=0;
    //ooi[3]=0;
    separator *sep=new separator(2,firsttest,ooi,0.5);
    sep->print();
    cout<<endl<<endl;

    tree *root=new tree(2,0.5);
    root->add(a);
    root->add(b);
    root->add(c);
    root->add(d);
    root->add(e);
    root->findsepbf();
    delete a,b;
}
