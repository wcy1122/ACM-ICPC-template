#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#define N 400010
#define Pi atan2(0,-1)
using namespace std;
int n,m,L,len,rev[N];
struct comp{
  double r,i;
  comp operator+(const comp &x)
  const{return (comp){r+x.r,i+x.i};}
  comp operator-(const comp &x)
  const{return (comp){r-x.r,i-x.i};}
  comp operator*(const comp &x)
  const{return (comp){r*x.r-i*x.i,r*x.i+i*x.r};}
}a[N],b[N],ans[N],t[N];
 
void DFT(comp *x,int n,int inv)
{
  for(int i=0;i<n;i++)t[rev[i]]=x[i];
  for(int i=0;i<n;i++)x[i]=t[i];
  for(int i=1,d=2;i<=L;i++,d<<=1)
  {
    comp w0=(comp){cos(2*Pi*inv/d),sin(2*Pi*inv/d)},w,u,v;
    for(int j=0,k;j<n;j+=d)
      for(k=j,w=(comp){1,0};k<j+(d>>1);k++,w=w*w0)
        u=x[k],v=x[k+(d>>1)]*w,x[k]=u+v,x[k+(d>>1)]=u-v;
  }
  if(inv==-1)for(int i=0;i<n;i++)x[i].r/=n;
}
 
int main()
{
  int x;
  scanf("%d%d",&n,&m);
  for(int i=0;i<=n;i++)
    scanf("%d",&x),a[i]=(comp){x,0};
  for(int i=0;i<=m;i++)
    scanf("%d",&x),b[i]=(comp){x,0};
  for(len=1,L=0;len<=max(m,n)*2;len<<=1,L++);
  for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|(i&1)<<(L-1);
  DFT(a,len,1);DFT(b,len,1);
  for(int i=0;i<len;i++)ans[i]=a[i]*b[i];
  DFT(ans,len,-1);
  for(int i=0;i<=n+m;i++)printf("%d\n",int(ans[i].r+0.5));
  return 0;
}
