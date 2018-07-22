#include<iostream> 
#include<cstdio> 
#include<cstdlib> 
#include<cstring> 
#include<string> 
#include<cmath> 
#include<algorithm> 
#define N 510
#define M 124760*2
using namespace std;
int n,m,ans,cnt,check[N],fa[N],parent[N],mate[N];
int k,la[N],ff[M],l,r,q[M],flag[N];
struct node{int a,b;}map[M];

void add(int a,int b)
{
  map[++k]=(node){a,b};ff[k]=la[a];la[a]=k;
  map[++k]=(node){b,a};ff[k]=la[b];la[b]=k;
}

int find(int x)
{
  if(fa[x]==x)return x;
  return fa[x]=find(fa[x]);
}

int lca(int x,int y)
{
  x=find(x);y=find(y);cnt++;
  while(1)
  {
    if(check[x]==cnt)return x;
	if(x)check[x]=cnt,x=find(parent[mate[x]]);
	if(check[y]==cnt)return y; 
	if(y)check[y]=cnt,y=find(parent[mate[y]]); 	
  }
} 

void merge(int x,int y,int t)
{
  while(find(x)!=t)
  {
	parent[x]=y;
	if(flag[mate[x]]==2)
	  q[r]=mate[x],flag[q[r]]=1,r++;
    if(find(x)==x)fa[x]=t;
	if(find(mate[x])==mate[x])fa[mate[x]]=t;
	y=mate[x];x=parent[y];
  }
}

int bfs(int S)
{
  for(int i=1;i<=n;i++)fa[i]=i,flag[i]=0;
  l=1;r=2;q[1]=S;flag[S]=1;parent[S]=0;
  while(l<r)
  {
    int x=q[l];l++;
	for(int a=la[x];a;a=ff[a])
	{
	  int y=map[a].b;
	  if(!flag[y])
	  {
		parent[y]=x;flag[y]=2;
		if(!mate[y])
		{
		  while(y)
		  {
		    int t=mate[parent[y]];
		    mate[y]=parent[y];
		    mate[parent[y]]=y;y=t;
		  }
		  return 1;
		}
		q[r]=mate[y];flag[q[r]]=1;r++;continue;
	  }
	  if(flag[y]==1&&find(x)!=find(y))
	  {
		int t=lca(x,y);
		merge(x,y,t);merge(y,x,t);
	  }
    }	
  }
  return 0;
}

int main()
{
  int a,b;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++)scanf("%d%d",&a,&b),add(a,b);
  for(int i=1;i<=n;i++)if(!mate[i])ans+=bfs(i);
  printf("%d\n",ans);
  for(int i=1;i<=n;i++)printf("%d ",mate[i]);
  printf("\n");
  return 0;
}
