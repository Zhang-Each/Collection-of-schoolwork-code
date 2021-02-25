#include<stdio.h>
#define MAX 100001
int main()
{
    int i,j,N,a[MAX],b[MAX],count;
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        scanf("%d",&a[i]);
        b[a[i]]=i;
    }
    count=0;
    for(j=1;j<N;j++)
    {
        for(;b[j]!=j;)
        {
            for(;b[0]!=0;)
            {
                count++;
                int t=b[b[0]];
                b[b[0]]=b[0];
                b[0]=t;
            }
            if(b[j]!=j)
            {
                count++;
                int t=b[j];
                b[j]=b[0];
                b[0]=t;
            }
        }
    }
    printf("%d",count);
    return 0;
}