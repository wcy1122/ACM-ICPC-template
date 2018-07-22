#define ll long long
#define mod 998244353
void NTT(ll *x,int n,int inv)
{
  for(int i=0;i<n;i++)t[rev[i]]=x[i];
  for(int i=0;i<n;i++)x[i]=t[i];
  for(int i=1,d=2;i<=L;i++,d<<=1)
  {
  	ll w0=Pow(3,(mod-1)/d),u,v,w;//Ô­¸ùÊÇ3
    for(int j=0,k;j<n;j+=d)
      for(k=j,w=1;k<j+(d>>1);k++,w=w*w0%mod)
      {
        u=x[k];v=x[k+(d>>1)]*w%mod;
		x[k]=(u+v)%mod;x[k+(d>>1)]=(u-v+mod)%mod;
	  }
  }
  if(inv==-1)
  {
  	ll y=Pow(n,mod-2);reverse(x+1,x+n);
    for(int i=0;i<len;i++)x[i]=x[i]*y%mod;
  }
}

int main()
{
  NTT(a,len,1);NTT(b,len,1);
  for(int i=0;i<len;i++)a[i]=a[i]*b[i]%mod;
  NTT(a,len,-1);
}
