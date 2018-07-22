#include<bits/stdc++.h>
#define N 1005
using namespace std;
int n1,n2,m,ans,e[N][N],mate[N],flag[N];

int dfs(int x)
{
  for(int i=1;i<=n1;i++)
    if(!flag[i]&&e[x][i])
    {
	  flag[i]=1;
	  if(!mate[i]||dfs(mate[i]))
	    {mate[i]=x;return 1;}
	}
  return false;
}

int main()
{
  int a,b;
  scanf("%d%d%d",&n1,&n2,&m);
  for(int i=1;i<=m;i++)
    scanf("%d%d",&a,&b),e[b][a]=1;
  for(int i=1;i<=n2;i++)
  {
    memset(flag,0,sizeof(flag));
    ans+=dfs(i);
  }
  printf("%d\n",ans);
  for(int i=1;i<=n1;i++)printf("%d ",mate[i]);
  printf("\n");
  return 0;
} 
