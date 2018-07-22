#include<bits/stdc++.h>
#define N 100005
#define M 400005
using namespace std;
int n,m,cd[N],rd[N],d[N],tot,ans[M];
int Tx,k=1,la[N],ff[M],now[N],used[M];
struct node{int a,b;}e[M];

void add(int a,int b)
{
  e[++k]=(node){a,b};
  ff[k]=la[a];la[a]=k;now[a]=la[a];
}

int get(int e)
{
  return (e&1)?-(e>>1):(e>>1);
}
//无向边正向走返回+，反向走返回- 
void dfs1(int x)
{
  for(;now[x];now[x]=ff[now[x]])
  {
  	int a=now[x];
  	if(used[a])continue;
    used[a]=1;used[a^1]=1;
	dfs1(e[a].b);ans[++tot]=get(a);
  }
}

bool solve1()
{
  int a,b;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d",&a,&b);
	add(a,b);add(b,a);d[a]++;d[b]++;
  }
  for(int i=1;i<=n;i++)
    if(d[i]&1)return false;
  for(int i=1;i<=n;i++)
  {
    if(!la[i])continue;
	dfs1(i);
    if(tot<m)return false;
    return true;
  }
}
//无向图 

void dfs2(int x)
{
  for(;now[x];now[x]=ff[now[x]])
  {
  	int a=now[x];
    if(used[a])continue;
    used[a]=1;dfs2(e[a].b);
    ans[++tot]=a-1;
  }
}

bool solve2()
{
  int a,b; 
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d",&a,&b);
	add(a,b);cd[a]++;rd[b]++;
  }
  for(int i=1;i<=n;i++)
    if(rd[i]!=cd[i])return false;
  for(int i=1;i<=n;i++)
  {
    if(!la[i])continue;
	dfs2(i);
    if(tot<m)return false;
    return true;
  }
}
//有向图 

int main()
{
  scanf("%d",&Tx);
  bool tmp=(Tx==1)?solve1():solve2();
  if(!tmp)printf("NO\n");
  else
  {
    printf("YES\n");
    for(int i=m;i;i--)printf("%d ",ans[i]);
    printf("\n");
  }
  return 0;
} 
