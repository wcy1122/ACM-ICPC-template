#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#define N 100010
#define M 1000010
using namespace std;
int n,m,Q,tot,fa[N+M],ans[N],e[N];
int st[N],end[N],flag[M],fx[N];
struct node{int a,b,c,pos;}map[M],ma[M];
struct wbs{int type,a,b;}q[N];
struct point{int c[2],fa,maxn,pos,num,rev;}t[N+M];
bool cmp1(const node &x,const node &y)
{return x.a<y.a||(x.a==y.a&&x.b<y.b);}
bool cmp2(const node &x,const node &y)
{return x.c<y.c;}
 
int erfen(int x,int y)
{
  int l=st[x],r=end[x];
  while(r-l>1)
  {
    int mid=l+r>>1;
    if(map[mid].b<=y)l=mid;
    else r=mid-1;
  }
  return map[l].b==y?l:r;
}
 
int find(int x)
{
  if(!fx[x])return x;
  return fx[x]=find(fx[x]);
}
 
class lct
{
  void pushdown(int x)
  {
    if(!t[x].rev)return;
    int lc=t[x].c[0],rc=t[x].c[1];
    t[lc].rev^=1;swap(t[lc].c[0],t[lc].c[1]);
    t[rc].rev^=1;swap(t[rc].c[0],t[rc].c[1]);
    t[x].rev=0;
  }
  void update(int x)
  {
    int lc=t[x].c[0],rc=t[x].c[1];
    t[x].maxn=t[x].num;t[x].pos=x;
    if(t[lc].maxn>t[x].maxn)
      t[x].maxn=t[lc].maxn,t[x].pos=t[lc].pos;
    if(t[rc].maxn>t[x].maxn)
      t[x].maxn=t[rc].maxn,t[x].pos=t[rc].pos;
  }
  void rotate(int x,int k)
  {
    int y=t[x].fa,f=(t[t[y].fa].c[1]==y);
    pushdown(y);pushdown(x);
    if(!t[y].fa)fa[x]=fa[y];
    t[x].fa=t[y].fa;t[t[y].fa].c[f]=x;
    t[y].fa=x;t[y].c[k]=t[x].c[k^1];
    t[t[y].c[k]].fa=y;t[x].c[k^1]=y;
    update(y);
  }
  void splay(int x,int des)
  {
    pushdown(x);
    if(x==des)return;
    while(t[x].fa!=des)
    {
      int y=t[x].fa,f=(t[y].c[1]==x);
      if(t[y].fa==des)rotate(x,f);
      else
      {
        if((t[t[y].fa].c[1]==y)==f)
          rotate(y,f),rotate(x,f);
        else rotate(x,f),rotate(x,f^1);
      }
    }
    update(x);
  }
  void access(int x)
  {
    for(int y=0;x;y=x,x=fa[x])
    {
      splay(x,0);
      t[t[x].c[1]].fa=0;fa[t[x].c[1]]=x;
      t[x].c[1]=y;fa[y]=0;t[y].fa=x;
      update(x);
    }
  }
  int lca(int x,int y)
  {
    access(x);
    for(splay(y,0);fa[y];splay(y,0))y=fa[y];
    return y;
  }
  public:
  void link(int x,int y)
  {
    access(x);splay(x,0);
    swap(t[x].c[0],t[x].c[1]);
    t[x].rev^=1;fa[x]=y;
  }
  void cut(int x,int y)
  {
    access(x);splay(y,0);
    if(fa[y]==x)swap(x,y);splay(x,0);
    t[t[x].c[0]].fa=0;
    fa[t[x].c[0]]=fa[x];
    t[x].c[0]=fa[x]=0;
    update(x);
  }
  int qry(int x,int y)
  {
    int pos=lca(x,y),res=pos;
    access(x);splay(x,0);splay(pos,x);if(t[t[pos].c[1]].maxn>t[res].num)res=t[t[pos].c[1]].pos;
    access(y);splay(y,0);splay(pos,y);if(t[t[pos].c[1]].maxn>t[res].num)res=t[t[pos].c[1]].pos;
    return res;
  }
}T;
 
int main()
{
  int a,b,c,type;
  scanf("%d%d%d",&n,&m,&Q);
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d%d",&a,&b,&c);
    if(a>b)swap(a,b);map[i]=(node){a,b,c,i};ma[i]=map[i];
    t[i+n].maxn=c;t[i+n].num=c;t[i+n].pos=i;
  }
  sort(map+1,map+m+1,cmp1);
  for(int i=1;i<=m;i++)
    if(map[i].a>map[i-1].a)
      st[map[i].a]=i,end[map[i-1].a]=i-1;
  end[map[m].a]=m;
  for(int i=1;i<=Q;i++)
  {
    scanf("%d%d%d",&type,&a,&b);
    if(a>b)swap(a,b);q[i]=(wbs){type,a,b};
    if(type==2)flag[e[i]=map[erfen(a,b)].pos]=1; 
  }
  sort(map+1,map+m+1,cmp2);
  for(int i=1,sum=0;i<=m&&sum<n-1;i++)
  {
    if(flag[map[i].pos])continue;
    int a=map[i].a,b=map[i].b,x=find(a),y=find(b);
    if(x!=y)fx[y]=x,T.link(a,map[i].pos+n),T.link(b,map[i].pos+n),sum++;
  }
  for(int i=Q;i;i--)
  {
    int a=q[i].a,b=q[i].b,l=T.qry(a,b)-n;
    if(q[i].type==2)
    {
      if(ma[l].c>ma[e[i]].c)
      {
        T.cut(ma[l].a,l+n);T.cut(ma[l].b,l+n);
        T.link(a,e[i]+n);T.link(b,e[i]+n);
      }
    } 
    else ans[++tot]=ma[l].c;
  }
  for(int i=tot;i;i--)printf("%d\n",ans[i]);
  return 0;
}
