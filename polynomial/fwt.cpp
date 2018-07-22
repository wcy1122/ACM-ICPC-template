void FWT(ll *a,int n)
{
  for(int d=1;d<n;d<<=1)
    for(int m=d<<1,i=0;i<n;i+=m)
      for(int j=0;j<d;j++)
      {
	    ll x=a[i+j],y=a[i+j+d];
	    a[i+j]=x+y;a[i+j+d]=x-y;
	    //xor:a[i+j]=x+y,a[i+j+d]=x-y;  
        //and:a[i+j]=x+y;  
        //or:a[i+j+d]=x+y;  
	  }
}

void UFWT(ll *a,int n)
{
  for(int d=1;d<n;d<<=1)
    for(int m=d<<1,i=0;i<n;i+=m)
      for(int j=0;j<d;j++)
      {
	    ll x=a[i+j],y=a[i+j+d];
	    a[i+j]=x+y>>1,a[i+j+d]=x-y>>1;
	    //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;  
        //and:a[i+j]=x-y;  
        //or:a[i+j+d]=y-x; 
	  }
}

int main()
{
  FWT(a,len);FWT(b,len);
  for(int i=0;i<=len;i++)a[i]*=b[i];
  UFWT(a,len);
}
