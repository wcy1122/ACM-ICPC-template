#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,m,cnt,q[N],top,dfn[N],low[N],flag[N];
int tot1,blo1[N],tot2,blo2[N];
int k=1,la[N],ff[N],check[N],iscut[N],isbridge[N];
struct node{int a,b;}e[N];

void add(int a,int b)
{
  e[++k]=(node){a,b};ff[k]=la[a];la[a]=k;
  e[++k]=(node){b,a};ff[k]=la[b];la[b]=k;
}

void dfs(int x,int pre)
{
  dfn[x]=++cnt;low[x]=cnt;
  for(int a=la[x];a;a=ff[a])
  {
  	int ed=(a>>1);
    if(!flag[ed])flag[ed]=1,q[++top]=ed;//把边入栈 
	if(!dfn[e[a].b])
	{
	  dfs(e[a].b,ed);
	  low[x]=min(low[x],low[e[a].b]);
	  if(low[e[a].b]>=dfn[x])
	  {
	  	iscut[x]++;
		//计算点割掉后多产生的联通块个数 
	  	tot1++;
	    while(top&&q[top]!=ed)blo1[q[top]]=tot1,top--;
	    blo1[ed]=tot1;top--;
	  }
	  //点双联通分量
	  if(low[e[a].b]>dfn[x])isbridge[ed]=1;
	  //判断割边 
	}
	else if(ed!=pre)low[x]=min(low[x],dfn[e[a].b]);
  }
}

void solve(int x,int now)
{
  check[x]=1;blo2[x]=now;
  for(int a=la[x];a;a=ff[a])
    if(!check[e[a].b]&&!isbridge[a>>1])
      solve(e[a].b,now);
} 
//求边双联通分量 

int main()
{
  int a,b;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++)
    scanf("%d%d",&a,&b),add(a,b);
  for(int i=1;i<=n;i++)if(!dfn[i]){
	dfs(i,0);//求割点桥边点双 
	if(iscut[i]==1)iscut[i]=0;
  }
  for(int i=1;i<=n;i++)if(!check[i])solve(i,++tot2);
  //求边双 
  for(int i=1;i<=m;i++)cout<<blo1[i]<<' ';cout<<endl;
  //blo1 每条边属于的点双联通分量 
  for(int i=1;i<=n;i++)cout<<blo2[i]<<' ';cout<<endl;
  //blo2 每个点属于的边双联通分量 
  for(int i=1;i<=n;i++)cout<<iscut[i]<<' ';cout<<endl;
  //iscut 去掉这个点后分成的联通块数量
  for(int i=1;i<=m;i++)cout<<isbridge[i]<<' ';cout<<endl;
  //isbridge 是否桥边 
  return 0;
}
