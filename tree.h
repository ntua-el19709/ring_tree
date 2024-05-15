#include <bits/stdc++.h>
#include "separator.h"

using namespace std;

bool double_equals(long double a,long  double b,long  double epsilon = 0.00001)
{
    return abs(a - b) < epsilon;
}

class tree{
public:
    int d,np,mass,nl,nr,c,check;
    vector<point *> points,subset;
    bool isleaf;
    long double r;
    separator *sep;
    tree *lchild,*rchild;

    tree(int vd,long double vr){
        d=vd;
        c=pow(2,d);//doubling dimension
        r=vr;
        np=0;
        mass=0;
        nl=0;
        nr=0;
        bool isleaf=0;
        sep= nullptr;
        lchild=nullptr;
        rchild=nullptr;

    };
    ~tree(){
        if(lchild!=nullptr)delete lchild;
        if(rchild!=nullptr)delete rchild;
        if(sep!=nullptr)delete sep;
        for(int i=0;i<np;i++){
            delete points[i];
        }
        points.clear();
    }
    add(point* &a){
        np++;
        mass++;
        points.push_back(new point(a));
    }

    int checkmassbalance(const separator* s){
        const point *cen=s->center;
        const long double rs=s->rs;
        int ans=0,le=0,ri=0;
        for(int i=0;i<np;i++){
            long double td=dist(cen,points[i]);
            if(td>=rs && td<=rs+2*r || double_equals(td,rs) ||double_equals(td,rs+2*r))ans++;

            if(td<=rs+r)le++;
            else ri++;
        }
        if (double(min(ri,le))/np<1.0/(c+1))return -1;
        else return ans;
    };

    void tryall(int i,int *inco){
        if(i==np){
            if(subset.size()!=d+1)return;
            separator *possep=new separator(d,subset,inco,r);
            int temass=checkmassbalance(possep);
            if(temass!=-1 && temass<mass){//found better separator
                if(sep!=nullptr)delete sep;
                sep=possep;
                mass=temass;
            }
            else delete possep;
            return;
        }
        else if(np-i<d+1-subset.size() || subset.size()>d+1)return;
        tryall(i+1,inco);
        subset.push_back(points[i]);
        for(int j=0;j<3;j++){
            inco[subset.size()-1]=j;
            tryall(i+1,inco);
        }
        subset.pop_back();
    }

    findsepbf(){
        check=0;
        if(subset.size()!=0)subset.clear();
        int incenout[d+1];
        tryall(0,incenout);
        sep->print();
        cout<<mass<<endl;
    }
};
