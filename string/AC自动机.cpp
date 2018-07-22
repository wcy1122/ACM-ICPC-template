class AC_machine
{
  public:
  void build(char *s,int len,int pos) 
  {
    int x=0,num;
    for(int i=1;i<=len;i++)
    {
      if(!ch[x][s[i]-‘a’])ch[x][s[i]-‘a’]=++cnt;
      x=ch[x][s[i]-‘a’];
    }
  }
  void get_fail()
  {
    int l=1,r=1;
    for(int i=1;i<=52;i++)if(ch[0][i])q[r++]=ch[0][i];
    while(l<r)
    {
      int x=q[l++];
      for(int i=0;i<52;i++)
      {
        if(!ch[x][i]){ch[x][i]=ch[fail[x]][i];continue;}
        q[r]=ch[x][i];fail[q[r++]]=ch[fail[x]][i];
      }
    }
  }
}T;
