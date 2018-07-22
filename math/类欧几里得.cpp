#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,b,c;
ll f(ll a,ll b,ll c,ll n)
{
  if(!c)return 0;
  ll m=(a*n+b)/c;
  if(a<c&&b<c)return n*m-f(c,c-b-1,a,m-1);
  return (a/c)*n*(n+1)/2+(b/c)*(n+1)+f(a%c,b%c,c,n);
}
//(ax+b)/c在0到n上的正整数点个数
//记得加上 c/a+1 
int main()
{
  scanf("%lld%lld%lld",&a,&b,&c);
  printf("%lld\n",f(a,c%a,b,c/a)+c/a+1);
  return 0;
}
