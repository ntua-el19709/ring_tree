#include <bits/stdc++.h>

using namespace std;

class point{
public:
    int d;

    /*
    vector<double> x;
    point(int vd) : d(vd), x(vector<double>(vd)) {}
    point(int vd, const vector<double>& vx) : d(vd), x(vx) {}
*/
    long double *x;
    point(int vd){
        d=vd;
        x= new long double[d];
    };
    point(int vd, long double *vx){
        d=vd;
        x=new long double[d];
        for(int i=0;i<d;i++)
            x[i]=vx[i];
    };
    point(const point* a){
        d=a->d;
        x=new long double[d];
        for(int i=0;i<d;i++)
            x[i]=a->x[i];
    };
    ~point(){
        delete x;
    };
    void print(){
        cout<<"point: ";
        for(int i=0;i<d;i++){
            cout<<x[i]<<" ";
        }
        cout<<endl;
    };

    friend void print(const point* a){
        cout<<"point: ";
        for(int i=0;i<a->d;i++){
            cout<<a->x[i]<<" ";
        }
        cout<<endl;
    };

    friend long double dist(const point* a, const point* b){
        long double ans=0;
        const int d1=a->d,d2=b->d;
        if(d1!=d2)return -1;
        for(int i=0;i<d1;i++)ans+=(b->x[i]-a->x[i])*(b->x[i]-a->x[i]);
        ans=sqrt(ans);
        return ans;
    }
};
