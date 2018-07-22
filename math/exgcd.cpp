#include<iostream>
#include<cstdio>
using namespace std;
int a,b,x,y;
void gcd(int a,int b)
{
  if(b==0){x=1;y=0;return;}
  else{gcd(b,a%b);int t=x;x=y;y=t-a/b*y;}
}
int main()
{
  scanf("%d%d",&a,&b);
  gcd(a,b);printf("%d\n",(x+b)%b);
  return 0;
}
