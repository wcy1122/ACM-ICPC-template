#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int n,top=0;
struct point{
  int a,b;
  bool operator<(point p)const{return a<p.a||(a==p.a&&b<p.b);}
  int operator*(point p)const{return a*p.b-b*p.a;}
  point operator-(point p)const{return (point){a-p.a,b-p.b};}
}s[50010],q[50010];
 
int main()
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++) scanf("%d%d",&s[i].a,&s[i].b);
  sort(s+1,s+n+1);top=0;
  for(int i=1;i<=n;i++)
  {
    while(top>1 && (q[top]-q[top-1])*(s[i]-q[top])<=0) top--;
    q[++top]=s[i];
  }int sum=top;
   
  for(int i=n-1;i>0;i--)
  {
    while(top>sum && (q[top]-q[top-1])*(s[i]-q[top])<=0) top--;
    q[++top]=s[i];  
  }
  printf("%d\n",top-1);
  return 0;
}
