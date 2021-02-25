#include<stdio.h>
#define MAX 101
int compare(int x[],int y[],int n);
void percdown(int a[],int i,int n);
void print(int kind,int n,int x[]);
int main()
{
    int i,j,n,m,a[MAX],b[MAX],d[MAX];
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    for(i=0;i<n;i++)
        scanf("%d",&d[i]);
    //insertion sort
    int p,tmp;
    m=0;
    for(p=1;p<n;p++)
    {
        tmp=b[p];
        for(j=p;j>0&&b[j-1]>=tmp;j--) b[j]=b[j-1];
        b[j]=tmp;
        if(m==1)
        {
            print(1,n,b);
            m=0;
            return 0;
        }
        m=compare(b,d,n);
    }
    //heapsort
    for(i=n/2;i>=0;i--)
        percdown(a,i,n);
    for(i=n-1;i>0;i--)
    {
        m=compare(a,d,n);
        int t=a[0];
        a[0]=a[i];
        a[i]=t;
        percdown(a,0,i);
        if(m==1)
        {
            print(2,n,a);
            m=0;
            return 0;  
        }
    }
    return 0;
}

int compare(int x[],int y[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(x[i]!=y[i]) return 0;
    }
    return 1;
}

void percdown(int a[],int i,int n)
{
    int child,tmp;
    for(tmp=a[i];2*i+1<n;i=child)
    {
        child=2*i+1;
        if(child!=n-1&&a[child+1]>a[child]) 
            child++;
        if(tmp<a[child]) 
            a[i]=a[child];
        else break;
    }
    a[i]=tmp;
}

void print(int kind,int n,int x[])
{
    if(kind==1) printf("Insertion Sort\n");
    else printf("Heap Sort\n");
    int i;
    for(i=0;i<n;i++)
    {
        if(i==0) printf("%d",x[i]);
        else printf(" %d",x[i]);
    }
}