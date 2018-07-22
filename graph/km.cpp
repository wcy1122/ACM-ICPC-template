#include<bits/stdc++.h>
#define ll long long
#define inf 2100000000
#define N 1005
#define M 1000005
using namespace std;
int n,n1,n2,m,labl[N],labr[N],pl[N],pr[N],pre[N];
int e[N][N],q[N],flag[M],slack[N];ll ans;
void find(int x)
{
  int p;
  while(x)
  {
    p=pl[pre[x]];pr[x]=pre[x];
	pl[pre[x]]=x;x=p;
  }
}

void KM(int S)
{
  memset(flag,0,sizeof(flag));
  memset(slack,63,sizeof(slack));
  int l=1,r=2;q[1]=S;flag[S]=1;
  while(1)
  {
    while(l<r)
    {
      int x=q[l++]; 
      for(int y=1;y<=n;y++)
      {
      	int tmp=labl[x]+labr[y]-e[x][y];
	    if(flag[pr[y]]||slack[y]<tmp)continue;
		pre[y]=x;
	    if(!tmp)
	    {
	      if(!pr[y])return find(y);
	      q[r]=pr[y];flag[q[r]]=1;r++;
	    }
	    else slack[y]=tmp;
	  }
    }
    int delta=inf; 
    for(int i=1;i<=n;i++)
      if(!flag[pr[i]])delta=min(delta,slack[i]);
	for(int i=1;i<=n;i++)
	{
	  if(flag[i])labl[i]-=delta;
	  if(flag[pr[i]])labr[i]+=delta;
	  else slack[i]-=delta;
	}
	for(int i=1;i<=n;i++)
	  if(!flag[pr[i]]&&!slack[i])
	  {
		if(!pr[i])return find(i);
		q[r]=pr[i];flag[q[r]]=1;r++;
	  }
  }
}

void KM()
{
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
	  labl[i]=max(labl[i],e[i][j]);
  for(int i=1;i<=n;i++)KM(i);
}

int main()
{
  int a,b,c;
  scanf("%d%d%d",&n1,&n2,&m);n=max(n1,n2);
  for(int i=1;i<=m;i++)
    scanf("%d%d%d",&a,&b,&c),e[a][b]=c;
  KM();
  for(int i=1;i<=n;i++)ans+=labl[i]+labr[i];
  printf("%lld\n",ans);
  for(int i=1;i<=n1;i++)printf("%d ",e[i][pl[i]]?pl[i]:0);
  printf("\n"); 
  return 0;
}
