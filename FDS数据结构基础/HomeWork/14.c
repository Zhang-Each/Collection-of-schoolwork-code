#include<stdio.h>
#define MAX 1001
#define INF 123456789

int visit[MAX]={0};
int result[MAX],len=0;
int degree[MAX]={0};
int map[MAX][MAX]={0};

int main()
{
    int i,j,n,a[MAX];
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    for(i=0;i<n;i++)
    {
        if(a[i]>=0)
        {
            int x=a[i]%n;
            if(x!=i)
            {
                degree[i]=(i+n-x)%n;
                for(j=0;j<degree[i];j++)
                {
                    map[(x+j)%n][i]=1;
                }
            }
        }
    }
    /*
    for(i=0;i<n;i++)
    {
        printf("%d ",degree[i]);
    }
    /*
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
    */
    int q[MAX],rear=0,front=0;
    for(i=0;i<n;i++)
    {
        int u=-1,v,min=INF;
        for(j=0;j<n;j++)
        {
            if(visit[j]==0&&degree[j]==0)
            {
                if(a[j]<min)
                {
                    min=a[j];
                    u=j;
                }
            }
        }
        if(u==-1) break;
        visit[u]=1;
        q[rear++]=a[u];
        for(v=0;v<n;v++)
        {
            if(visit[v]==0&&map[u][v]==1)
            {
                degree[v]--;
                map[u][v]=0;
            }
        }
    }
    while(rear!=front)
    {
        if(q[front]>0)
        {
            result[len++]=q[front++];
        }
        else front++;
    }
    for(i=0;i<len;i++)
    {
        if(i==0) printf("%d",result[i]);
        else printf(" %d",result[i]);
    }
    return 0;
}