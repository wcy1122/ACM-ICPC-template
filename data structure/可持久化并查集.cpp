#include<bits/stdc++.h>
#define N 200005
using namespace std;
int n,m,pre,cnt,rt[N],size[N];
struct info{int lc,rc,val,size;}t[N*40];

class seg_tree{
  public:
  void build(int &x,int l,int r)
  {
  	x=++cnt;
    if(l==r){t[x].val=l;t[x].size=1;return;}
    int mid=l+r>>1;
    build(t[x].lc,l,mid);build(t[x].rc,mid+1,r);
  }
  void modify1(int &x,int pre,int l,int r,int pos,int val)
  {
  	x=++cnt;t[x]=t[pre];
    if(l==r){t[x].val=val;return;}
    int mid=l+r>>1;
    if(pos<=mid)modify1(t[x].lc,t[pre].lc,l,mid,pos,val);
    else modify1(t[x].rc,t[pre].rc,mid+1,r,pos,val);
  }
  void modify2(int &x,int pre,int l,int r,int pos,int val)
  {
  	x=++cnt;t[x]=t[pre];
    if(l==r){t[x].size+=val;return;}
    int mid=l+r>>1;
    if(pos<=mid)modify2(t[x].lc,t[pre].lc,l,mid,pos,val);
    else modify2(t[x].rc,t[pre].rc,mid+1,r,pos,val);
  }
  int qry1(int x,int l,int r,int pos)
  {
    if(l==r)return t[x].val;
    int mid=l+r>>1;
    if(pos<=mid)return qry1(t[x].lc,l,mid,pos);
    return qry1(t[x].rc,mid+1,r,pos);
  }
  int qry2(int x,int l,int r,int pos)
  {
    if(l==r)return t[x].size;
    int mid=l+r>>1;
    if(pos<=mid)return qry2(t[x].lc,l,mid,pos);
    return qry2(t[x].rc,mid+1,r,pos);
  }
}T;

int find(int p,int x)
{
  int pos=T.qry1(p,1,n,x);
  if(pos==x)return x;
  return find(p,pos);
}

int main()
{
  int tp,x,y,a,b;
  scanf("%d%d",&n,&m);T.build(rt[0],1,n);
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d",&tp,&x);x^=pre;rt[i]=rt[i-1];
    if(tp==1)
    {
	  scanf("%d",&y);y^=pre;
	  x=find(rt[i],x);a=T.qry2(rt[i],1,n,x);
	  y=find(rt[i],y);b=T.qry2(rt[i],1,n,y);
	  if(a<b)swap(x,y),swap(a,b);
	  T.modify1(rt[i],rt[i],1,n,y,x);
	  T.modify2(rt[i],rt[i],1,n,x,b);
	}
	if(tp==2)rt[i]=rt[x];
	if(tp==3)
	{
	  scanf("%d",&y);
	  printf("%d\n",pre=(find(rt[i],x)==find(rt[i],y)));
	}
  }
  return 0;
} 
