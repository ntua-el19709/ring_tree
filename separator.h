#include <bits/stdc++.h>
#include <Eigen/Dense>
#include "point.h"
using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

class separator{
public:
    int d;
    point *center;
    long double rs,r;
    separator(int vd){
        d=vd;
        center=new point(d);
    };
    ~separator(){
        delete center;
    };
    separator(int vd,const vector<point*> pts,const int *ooi,long double vr){//outorin=0 for inner 1 for central, 2 for outer
        vector<point*> points;
        int outorin[vd+1];
        for(int i=0;i<=vd;i++){
            points.push_back(new point(pts[i]));
            outorin[i]=ooi[i];
        }
        d=vd;
        r=vr;
        bool fi=false,allin=true,allcen=true,allout=true;
        for(int i=0;i<=vd;i++){
            if (outorin[i]==0 && fi==false){
                fi=true;
                point *temp=points[0];
                points[0]=points[i];
                points[i]=temp;
                outorin[i]=outorin[0];
                outorin[0]=0;
                allout=false;
                allcen=false;
            }
            if(outorin[i]==1 || outorin[i]==2)allin=false;
            if(outorin[i]==0 || outorin[i]==2)allcen=false;
            if(outorin[i]==1 || outorin[i]==0)allout=false;
        }

        if(!fi && !allcen && !allout){ //points on central and outer radius
            for(int i=0;i<=vd;i++){
                if (outorin[i]==1){
                    point *temp=points[0];
                    points[0]=points[i];
                    points[i]=temp;
                    outorin[i]=outorin[0];
                    outorin[0]=1;
                    break;
                }
            }
            long double p1x[d];
            for(int i=0;i<d;i++){
                p1x[i]=points[0]->x[i];
            }
            MatrixXd M(d,d);
            VectorXd B1(d);
            VectorXd B2(d);

            for(int i=0;i<d;i++){
                long double b1=0;
                for(int j=0;j<d;j++){
                    M(i,j)=(p1x[j])-(points[i+1]->x[j]);
                    b1+=(p1x[j])*(p1x[j])-(points[i+1]->x[j])*(points[i+1]->x[j]);
                }
                B1(i)=(b1+r*r*(outorin[i+1]-1)*(outorin[i+1]-1))*0.5;
                B2(i)=r*(outorin[i+1]-1);
            }
            Eigen::PartialPivLU<MatrixXd> lu(M);
            VectorXd X1 = lu.solve(B1);
            VectorXd X2 = lu.solve(B2);
            long double a=-1.0,b=0,c=0;
            for(int i=0;i<d;i++){
                a+=X2(i)*X2(i);
                b-=2*(p1x[i]-X1(i))*X2(i);
                c+=(p1x[i]-X1(i))*(p1x[i]-X1(i));
            }
            long double D=b*b-4*a*c;
            long double R1=(-b+sqrt(D))/(2*a),R2=(-b-sqrt(D))/(2*a);
            rs=max(R1,R2);
            center= new point(d);
            for(int i=0;i<d;i++){
                center->x[i]=X1(i)+X2(i)*rs;
            }
            rs-=r;
            for(int i=0;i<=vd;i++)delete points[i];
            points.clear();
            return;
        }

        long double p1x[d];

        for(int i=0;i<d;i++){
            p1x[i]=points[0]->x[i];
        }
        MatrixXd M(d,d);
        VectorXd B1(d);
        VectorXd B2(d);
        if(allin || allcen || allout){
            for(int i=0;i<d;i++){
                long double b1=0;
                for(int j=0;j<d;j++){
                    M(i,j)=(p1x[j])-(points[i+1]->x[j]);
                    b1+=(p1x[j])*(p1x[j])-(points[i+1]->x[j])*(points[i+1]->x[j]);
                }
                B1(i)=(b1)*0.5;
            }
        }
        else{
            for(int i=0;i<d;i++){
                long double b1=0;
                for(int j=0;j<d;j++){
                    M(i,j)=(p1x[j])-(points[i+1]->x[j]);
                    b1+=(p1x[j])*(p1x[j])-(points[i+1]->x[j])*(points[i+1]->x[j]);
                }
                B1(i)=(b1+r*r*outorin[i+1]*outorin[i+1])*0.5;
                B2(i)=r*outorin[i+1];
            }
        }
        Eigen::PartialPivLU<MatrixXd> lu(M);
        VectorXd X1 = lu.solve(B1);
        if(allin || allcen || allout){//all in or all central or all out
            center= new point(d);
            long double R=0;
            for(int i=0;i<d;i++){
                center->x[i]=X1(i);
                R+=(p1x[i]-X1(i))*(p1x[i]-X1(i));
            }
            R=sqrt(R);
            if(allin)rs=R;
            else if(allcen)rs=R-r;
            else rs=R-2*r;
        }
        else{
            VectorXd X2 = lu.solve(B2);
            long double a=-1.0,b=0,c=0;
            for(int i=0;i<d;i++){
                a+=X2(i)*X2(i);
                b-=2*(p1x[i]-X1(i))*X2(i);
                c+=(p1x[i]-X1(i))*(p1x[i]-X1(i));
            }
            long double D=b*b-4*a*c;
            long double R1=(-b+sqrt(D))/(2*a),R2=(-b-sqrt(D))/(2*a);
            rs=max(R1,R2);
            center= new point(d);
            for(int i=0;i<d;i++){
                center->x[i]=X1(i)+X2(i)*rs;
            }
        }
        for(int i=0;i<=vd;i++)delete points[i];
        points.clear();
    };
    void print(){
        cout<<"center:"<<endl;
        for(int i=0;i<d;i++){
            cout<<center->x[i]<<" ";
        }
        cout<<endl<<"R:"<<endl<<rs<<endl;
    };
};
