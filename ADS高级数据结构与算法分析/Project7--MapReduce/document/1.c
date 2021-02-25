#include <stdio.h>

int FindMinSteps(int N, int K);

int main()
{
  int N, K;
	
	scanf("%d%d", &N, &K);
	
	printf("%d", FindMinSteps(N, K));
	
	return 0;
}	


int min(int a,int b)
{
    if(a>b) return b;
    else return a;
}

int FindMinSteps(int N, int K)
{
    //printf("%d %d\n",N,K);
    if(N==1) 
        return 0;
    else if(N>=2&&N<=11) 
        return 1;
    int a[100001];
    int i,j;
    a[1]=0;
    for(i=2;i<=11;i++){
        a[i]=1;
    }
    for(i=12;i<=N;i++)
    {
        int minx=1000000;
        for(j=i-10;j<=i-1;j++)
        {
            if(a[j]<minx)
                minx=a[j];
        }
        if(i%K==0)
        {
            a[i]=min(minx,a[i/K])+1;
        }
        else a[i]=minx+1;
    }
    return a[N];
}