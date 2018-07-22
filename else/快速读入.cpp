#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
inline int get()
{
  char ch;int v;
  while(!isdigit(ch=getchar()));v=ch-48;
  while(isdigit(ch=getchar()))v=v*10+ch-48;
  return v;
}
int main()
{
  int x;
  x=get();
} 
 
