int main()
{
  scanf(" %s",s+1);n=strlen(s+1);g[0]=-1;//模式串
  for(int i=1;i<=n;i++)
  {
  	int x=g[i-1];
    while(x>=0&&s[x+1]!=s[i])x=g[x];
	  g[i]=x+1;
  }
  scanf(" %s",t+1);n=strlen(t+1);f[0]=0;//匹配串
  for(int i=1;i<=n;i++)
  {
    int x=f[i-1];
    while(x>=0&&s[x+1]!=t[i])x=g[x];
    f[i]=x+1;
  }
  return 0;
}
