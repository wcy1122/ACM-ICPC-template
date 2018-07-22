class SAM{
  public:
  int build(int x,int c){
    int nx=++cnt;f[nx]=f[x]+1;
    while(x&&!ch[x][c])ch[x][c]=nx,x=fa[x];
    if(!x)fa[nx]=1;
    else{
      int p=ch[x][c];
      if(f[p]==f[x]+1)fa[nx]=p;
      else{
        int np=++cnt;f[np]=f[x]+1;
        memcpy(ch[np],ch[p],sizeof(ch[p]));
        fa[np]=fa[p];fa[nx]=fa[p]=np;
        while(x&&ch[x][c]==p)ch[x][c]=np,x=fa[x];
      }
    }
    return nx;
  }
}S;
int main()
{
  int pos;
  scanf(" %s",s+1);
  for(int i=1;i<=n;i++)pos=S.build(i,pos);
  return 0;
}
