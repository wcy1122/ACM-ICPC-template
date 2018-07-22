#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#define N 100010
using namespace std;
int n,m,cnt[N],x[N],y[N],t[N],sa[N];
int g[N][20],rank[N],height[N]; 
char s[N];

bool cmp(int *g,int a,int b,int l)
{return  g[a]==g[b]&&g[a+l]==g[b+l];}

void get_sa()
{
  m=128;
  for(int i=1;i<=n;i++)cnt[x[i]=s[i]]++;
  for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
  for(int i=n;i;i--)sa[cnt[x[i]]--]=i;
  for(int j=1,tot=0;tot<=n;m=tot,j<<=1)
  {
    tot=0;for(int i=n-j+1;i<=n;i++)y[++tot]=i;
    for(int i=1;i<=n;i++)if(sa[i]>j)y[++tot]=sa[i]-j;
    for(int i=1;i<=n;i++)t[i]=x[y[i]];
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)cnt[t[i]]++;
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i;i--)sa[cnt[t[i]]--]=y[i];
	tot=2;swap(x,y);x[sa[1]]=1;
	for(int i=2;i<=n;i++)
	  x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?tot-1:tot++;
  }
} 

void get_height()
{
  for(int i=1;i<=n;i++)rank[sa[i]]=i;
  for(int i=1,j,k=0;i<=n;height[rank[i++]]=k)
  for(k=k?k-1:0,j=sa[rank[i]-1];s[i+k]==s[j+k];k++);
  for(int i=1;i<=n;i++)printf("%d ",sa[i]);printf("\n");
  for(int i=2;i<=n;i++)printf("%d ",height[i]);printf("\n");
}

void get_rmq()
{
  memset(g,127,sizeof(g));
  for(int i=1;i<=n;i++)g[i][0]=height[i];
  for(int j=1;(1<<j)<=n;j++)
    for(int i=1;i<=n-(1<<j)+1;i++)
	  g[i][j]=min(g[i][j-1],g[i+(1<<j-1)][j-1]);
}

int get_lcp(int x,int y)
{
  x=rank[x];y=rank[y];
  if(x>y)swap(x,y);x++;
  int p=log2(y-x+1);
  return min(g[x][p],g[y-(1<<p)+1][p]);
}

int main()
{
  scanf("%s",s+1);n=strlen(s+1);
  get_sa();get_height();get_rmq();
  return 0;
}
