#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#define N 100010
#define eps 1e-7
using namespace std;
int n,tot;
double ans1,ans2;
struct point{
  double x,y;
  point operator+(const point &p)
  const{return (point){x+p.x,y+p.y};}
  point operator-(const point &p)
  const{return (point){x-p.x,y-p.y};}
  point operator*(const double &num)
  const{return (point){x*num,y*num};}
  double operator^(const point &p)
  const{return x*p.y-p.x*y;}
}t[N],p[N*2];
struct node{
  point p,v;double ang;
  bool operator<(const node &x)
  const{return ang<x.ang||(ang==x.ang&&(v^(x.p-p))<eps);}
}s[N*2],q[N*2];
bool pd(node a,point b){return (a.v^(b-a.p))<-eps;}
double get_ang(point p){return atan2(p.y,p.x);}
point get_jd(node a,node b)
{
  point x=a.p-b.p;
  double t=(b.v^x)/(a.v^b.v);
  return a.p+a.v*t;
}
   
void solve()
{
  sort(s+1,s+n+1);tot=1;
  for(int i=2;i<=n;i++)
    if(fabs(s[i].ang-s[i-1].ang)>eps)s[++tot]=s[i];
  int l=1,r=2;q[1]=s[1];q[2]=s[2];n=tot;
  for(int i=3;i<=n;i++)
  {
    while(l<r&&pd(s[i],get_jd(q[r],q[r-1])))r--;
    while(l<r&&pd(s[i],get_jd(q[l],q[l+1])))l++;
    q[++r]=s[i];
  }
  while(l<r&&pd(q[l],get_jd(q[r],q[r-1])))r--;
  while(l<r&&pd(q[r],get_jd(q[l],q[l+1])))l++;
  if(r-l<=1)return;
  q[r+1]=q[l];tot=0;
  for(int i=l;i<=r;i++)p[++tot]=get_jd(q[i],q[i+1]);
  p[tot+1]=p[1];
  for(int i=1;i<=tot;i++)ans2+=fabs((p[i]-p[1])^(p[i+1]-p[1]));
}
   
void prepare()
{
  double X1=t[1].x,Y1=t[1].y;
  double X2=t[2].x,Y2=t[2].y;
  for(int i=2;i<=n;i++)
  {
    double X3=t[i].x,Y3=t[i].y;
    double X4=t[i+1].x,Y4=t[i+1].y;
    double a=Y1-Y2-Y3+Y4,b=X2-X1-X4+X3;
    double c=X3*Y4-X4*Y3+X2*Y1-X1*Y2;
    double p1,p2,p3,p4;
    if(fabs(a)<eps){p1=0,p2=c/b,p3=1,p4=c/b;if(b>0)swap(p1,p3),swap(p2,p4);}
    else if(fabs(b)<eps){p1=c/a,p2=0,p3=c/a,p4=1;if(a<0)swap(p1,p3),swap(p2,p4);}
         else if(b<0)p1=0,p2=c/b,p3=1,p4=c/b-a/b;
              else p1=1,p2=c/b-a/b,p3=0,p4=c/b;
    point X1=(point){p1,p2},X2=(point){p3-p1,p4-p2};
    s[i]=(node){X1,X2,get_ang(X2)};
  }
  s[1]=(node){t[1],t[2]-t[1],get_ang(t[2]-t[1])};
} 
   
int main()
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
    scanf("%lf%lf",&t[i].x,&t[i].y);t[n+1]=t[1];
  for(int i=1;i<=n;i++)ans1+=((t[i]-t[1])^(t[i+1]-t[1]));
  prepare();solve();
  printf("%.4lf",ans2/ans1);
  return 0;
}
