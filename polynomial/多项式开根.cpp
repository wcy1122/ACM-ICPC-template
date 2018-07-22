#include<bits/stdc++.h>
#define ll long long
#define N 1000000
using namespace std;
int n,L,len,rev[N];
ll a[N],b[N],s[N],inv2,invb[N],w,t[N];
const ll mod=998244353;
struct number{ll r,i;};
number mul(number a,number b,ll p){
  ll x=(a.r*b.r%p+a.i*b.i%p*w%p)%p;
  ll y=(a.r*b.i%p+a.i*b.r%p+p)%p;
  return (number){x,y};
}

ll Pow(ll a,ll b,ll mod)
{
  ll res=1;
  while(b)
  {
    if(b&1)res=res*a%mod; 
    a=a*a%mod;b>>=1;
  }
  return res;
}

number r_Pow(number a,ll b,ll mod)
{
  number res=(number){1,0};
  while(b)
  {
    if(b&1)res=mul(res,a,mod);
    a=mul(a,a,mod);b>>=1;
  }
  return res;
}

ll legendre(ll a,ll p)
{
  return Pow(a,(p-1)>>1,p);
} 

ll solve(ll n,ll p)
{
  if(p==2)return 1; 
  if(legendre(n,p)==p-1)return -1; 
  ll a;
  while(1)
  {
    a=rand()%p;
	w=(a*a-n+p)%p;
    if(legendre(w,p)==p-1)break;
  }
  ll res=r_Pow((number){a,1},(p+1)>>1,p).r;
  return min(res,p-res);
}

void NTT(ll *x,int n,int inv)
{
  for(int i=0;i<n;i++)t[rev[i]]=x[i];
  for(int i=0;i<n;i++)x[i]=t[i];
  for(int i=1,d=2;i<=L;i++,d<<=1)
  {
  	ll w0=Pow(3,(mod-1)/d,mod),u,v,w;
    for(int j=0,k;j<n;j+=d)
      for(k=j,w=1;k<j+(d>>1);k++,w=w*w0%mod)
      {
        u=x[k];v=x[k+(d>>1)]*w%mod;
		x[k]=(u+v)%mod;x[k+(d>>1)]=(u-v+mod)%mod;
	  }
  }
  if(inv==-1)
  {
  	ll y=Pow(n,mod-2,mod);reverse(x+1,x+n);
    for(int i=0;i<len;i++)x[i]=x[i]*y%mod;
  }
}

inline void inverse(int n,ll *a,ll *b,ll *c)
{
  if(n==1)
  {
  	b[0]=Pow(a[0],mod-2,mod);
    return;
  }
  inverse((n+1)>>1,a,b,c);
  int len=0;
  for(len=1,L=0;len<=(n<<1);len<<=1,L++);
  for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|(i&1)<<(L-1);
  for(int i=0;i<n;i++)c[i]=a[i];
  for(int i=n;i<len;i++)c[i]=0;
  NTT(b,len,1);NTT(c,len,1);
  for(int i=0;i<len;i++)
    b[i]=(ll)(2-(ll)c[i]*b[i]%mod+mod)%mod*b[i]%mod;
  NTT(b,len,-1);
  for(int i=n;i<len;i++)b[i]=0;
}

void Sqrt(int n,ll *a,ll *b,ll *c)
{
  if(n==1)
  {
    b[0]=solve(a[0],mod);
    return;
  }
  Sqrt(n>>1,a,b,c);
  memset(invb,0,sizeof(invb));
  inverse(n>>1,b,invb,c);
  int len=0;
  for(len=1,L=0;len<=(n<<1);len<<=1,L++);
  for(int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|(i&1)<<(L-1);
  for(int i=0;i<n;i++)c[i]=a[i];
  for(int i=n;i<len;i++)c[i]=0;
  NTT(c,len,1);NTT(invb,len,1);
  for(int i=0;i<len;i++)c[i]=c[i]*invb[i]%mod*inv2%mod;
  NTT(c,len,-1);
  for(int i=0;i<n;i++)b[i]=(c[i]+b[i]*inv2%mod)%mod;
  for(int i=0;i<len;i++)cout<<b[i]<<' ';cout<<endl;
}

int main()
{
  scanf("%d",&n);
  inv2=Pow(2,mod-2,mod);
  for(int i=0;i<=n;i++)scanf("%d",&a[i]);
  for(len=1,L=0;len<=(n<<1);len<<=1,L++);
  Sqrt(len,a,b,s);//a是原多项式，b是答案 s是临时数组 
  for(int i=0;i<=n;i++)printf("%d ",b[i]);
  printf("\n");
  return 0;
} 
