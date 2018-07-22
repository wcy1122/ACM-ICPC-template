#include<bits/stdc++.h>
#define ll long long
using namespace std;
int m; 

int Pow(int a,int b)
{
  int res=1; 
  while(b)
  {
    if(b&1)res=(ll)res*a%m;
    a=(ll)a*a%m;b>>=1;
  }
  return res;
}

bool check(int x)
{
  int num=m-1;
  for(int i=2;i*i<=num;i++)
  {
    if(num%i)continue;
    while(!(num%i))num/=i;
    if(Pow(x,(m-1)/i)==1)return false;
  }
  if(num>1&&Pow(x,(m-1)/num)==1)return false;
  return true;
}

int main()
{
  scanf("%d",&m);//mod m 意义下的原根 
  for(int i=2;;i++)
  	if(check(i)){printf("%d\n",i);break;}
  return 0;
}
