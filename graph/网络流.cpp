ll dfs(int x,ll flow)
{
  if(x==T)return flow;
  ll res=0,tmp;
  for(int a=cur[x];a&&flow;a=ff[a])
  {
  	cur[x]=a;
    if(dep[e[a].b]==dep[x]+1&&e[a].c)
    {
      tmp=dfs(map[a].b,min(flow,e[a].c));
      e[a].c-=tmp;e[a^1].c+=tmp;res+=tmp;flow-=tmp;
    }
  }
  if(!res)dep[x]=-1;
  return res;
}
bool bfs()
{
  memset(dep,0,sizeof(dep));
  for(int i=S;i<=T;i++)cur[i]=la[i];
  int l=1,r=2;q[1]=S;dep[S]=1;
  while(l<r)
  {
    int x=q[l];l++;
    for(int a=la[x];a;a=ff[a])
      if(!dep[e[a].b]&&e[a].c)
        q[r]=e[a].b,dep[q[r]]=dep[x]+1,r++;
  }
  return dep[T];
}
int main()
{
  int a,b;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++)scanf("%d%d%d",&a,&b,&c),add(a,b,c);
  while(bfs(S,0))ans+=dfs(S,0);
  printf("%d\n",ans);
  return 0;
}

