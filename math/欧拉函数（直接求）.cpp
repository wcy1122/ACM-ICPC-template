#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
int n;ll ans;
ll phi(int x)
{
  ll res=x;
  for(int i=2;i*i<=x;i++)
    if(!(x%i))
    {
      res=res/i*(i-1);
      while(!(x%i))x/=i;
    }
  if(x>1)res=res/x*(x-1);
  return res;
}
 
int main()
{
  return 0;
}
