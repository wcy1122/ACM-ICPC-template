#define inf 2100000000
using namespace std;
int n,m,root,sum,null=4000005,s[4000010];
struct node{
int num,fa,c[2],maxl,maxr,maxn,sum,change,turn,size;}t[4000010];

class splay_tree
{
  public:
  void up(int x)
  {
    int lc=t[x].c[0],rc=t[x].c[1],maxx;
    t[x].maxl=max(t[lc].maxl,t[lc].sum+t[x].num+max(0,t[rc].maxl));
    t[x].maxr=max(t[rc].maxr,t[rc].sum+t[x].num+max(0,t[lc].maxr));
    maxx=max(0,t[lc].maxr)+max(0,t[rc].maxl)+t[x].num;
    t[x].maxn=max(maxx,max(t[lc].maxn,t[rc].maxn));
    t[x].size=t[lc].size+t[rc].size+1;t[x].sum=t[lc].sum+t[rc].sum+t[x].num;
  }
  void rotate(int x,int k)
  {
    int ff=t[t[t[x].fa].fa].c[0]==t[x].fa?0:1;
    t[t[x].fa].c[k]=t[x].c[k^1];
    t[t[x].c[k^1]].fa=t[x].fa;
    t[x].c[k^1]=t[x].fa;
    int temp=t[t[x].fa].fa;
    t[t[x].fa].fa=x;t[x].fa=temp;
    t[t[x].fa].c[ff]=x;
    up(t[x].c[k^1]);
  }
  void turn(int pos)
  {
    t[pos].turn^=1;swap(t[pos].c[0],t[pos].c[1]);
    swap(t[pos].maxl,t[pos].maxr); 
  }
  void change(int pos,int x)
  {
    t[pos].change=1;t[pos].num=x;t[pos].sum=t[pos].size*x;
    if(x>=0)t[pos].maxl=t[pos].maxr=t[pos].maxn=t[pos].sum;
    else t[pos].maxl=t[pos].maxr=t[pos].maxn=x;
  }
  void down(int x)
  {
    int lc=t[x].c[0],rc=t[x].c[1];
    if(t[x].change)change(lc,t[x].num),change(rc,t[x].num),t[x].change=0;
    if(t[x].turn)turn(lc),turn(rc),t[x].turn=0;
  }
  void build(int x,int l,int r)
  {
    t[x].num=t[x].sum=t[x].maxl=t[x].maxr=t[x].maxn=s[x];
    int mid;t[x].c[0]=t[x].c[1]=null;
    if(l<x)mid=(l+x-1)>>1,t[x].c[0]=mid,t[mid].fa=x,build(mid,l,x-1);
    if(r>x)mid=(x+r+1)>>1,t[x].c[1]=mid,t[mid].fa=x,build(mid,x+1,r);
    up(x);
  }
  void splay(int x,int pos)
  {
    int flag=0;
    while(!flag)
    {
      down(x);int fa=t[x].fa,fb=t[fa].fa;
      if(fa==pos||fb==pos)flag=1;
      if(fa==pos){rotate(x,t[fa].c[0]==x?0:1);continue;}
      rotate(x,t[fa].c[0]==x?0:1);rotate(x,t[fb].c[0]==x?0:1);
    }
    up(x);if(pos==root)root=x;
  }
  void select(int x,int des)
  { 
    int p=root,cnt=x+1;
    while(cnt)
    {
      int temp=t[t[p].c[0]].size;down(p);
      if(cnt==temp+1)break;
      if(cnt<=temp)p=t[p].c[0];
      else p=t[p].c[1],cnt-=temp+1;
    }
    if(p!=des)splay(p,des);
  }
}T;

int main()
{
  char str[10];int rt,temp,a,b,c,pos;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)scanf("%d",&s[i]);
  sum=++n;root=n>>1;t[root].fa=null;
  t[null].maxn=-inf;
  t[0].maxn=t[n].maxn=t[0].num=s[0]=t[n].num=s[n]=-inf;
  T.build(root,0,n);
  while(m--)
  {
    scanf(" %s",str+1);
    if(str[3]=='S')//pos后插入k个数
    {
      scanf("%d%d",&a,&b);n+=b;
      for(int i=sum+1;i<=n;i++)scanf("%d",&s[i]);
      T.select(a,root);T.select(a+1,t[root].c[1]);
      T.build(rt=sum+((b+1)>>1),sum+1,n);sum=n;
      temp=t[root].c[1];t[rt].fa=temp;t[temp].c[0]=rt;
      T.up(t[root].c[1]);T.up(root);
    }
    if(str[3]=='L')//pos后删除k个数
    {
      scanf("%d%d",&a,&b);
      T.select(a-1,root);T.select(a+b,t[root].c[1]);
      t[t[root].c[1]].c[0]=null;
      T.up(t[root].c[1]);T.up(root);
    }
    if(str[3]=='K')//pos后k个数改为c
    {
      scanf("%d%d%d",&a,&b,&c);
      T.select(a-1,root);T.select(a+b,t[root].c[1]);
      pos=t[t[root].c[1]].c[0];T.change(pos,c);
      T.up(t[root].c[1]);T.up(root);
    }
    if(str[3]=='V')//区间翻转
    {
      scanf("%d%d",&a,&b);
      T.select(a-1,root);T.select(a+b,t[root].c[1]);
      T.turn(t[t[root].c[1]].c[0]);
      T.up(t[root].c[1]);T.up(root);
    }
    if(str[3]=='T')//区间和
    {
      scanf("%d%d",&a,&b);
      T.select(a-1,root);T.select(a+b,t[root].c[1]);
      int temp=t[t[root].c[1]].c[0];
      printf("%d\n",t[temp].sum);
    }
    if(str[3]=='X')printf("%d\n",t[root].maxn);//最大子段和
  }
  return 0;
}
