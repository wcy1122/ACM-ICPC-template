#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
const int N=50000;
int tot,n,ans,check[50010],f[50010],p[50010];

int main()
{
  int i,j,a,b,d,pl,k;f[1]=1;
  for(i=2;i<=N;i++)
  {
    if(!check[i]) f[i]=-1,p[++tot]=i;
    for(j=1;j<=tot;j++)
    {
      if(i*p[j]>N) break;
      check[i*p[j]]=1;
      if(i%p[j]==0){f[i*p[j]]=0;break;}
      f[i*p[j]]=-f[i];
    }
  }
  return 0;
}
