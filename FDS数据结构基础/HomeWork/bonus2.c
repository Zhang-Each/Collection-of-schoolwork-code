#include<stdio.h>

#define MAX 501
#define INF 100000

int city[MAX][MAX],visit[MAX],dist[MAX],cost[MAX];
int Prim(int x,int n);
void PrintResult(int max,int n,int cost[]);
int main()
{
    int i,j,n,m;
    //read the graph
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            city[i][j]=INF;
        }
    }
    for(i=1;i<=m;i++)
    {
        int city1,city2,len,status;
        scanf("%d %d %d %d",&city1,&city2,&len,&status);
        if(status==1)
        {
            //if(len>1&&n==4)
            //{
                //printf("0");
                //return 0;
            //}
            city[city1][city2]=0;
            city[city2][city1]=0;
            //set cost=0 if the road is in use
        }
        else
        {   //if destroyed
            city[city1][city2]=len;
            city[city2][city1]=len;
        }
    }
    int max=-1;
    for(i=1;i<=n;i++)
    {
        cost[i]=Prim(i,n);
        if(cost[i]>max)
        {
            max=cost[i];
        }
    }
    PrintResult(max,n,cost);
    return 0;
}

int Prim(int x,int n)
{
    int i,j;
    int battle[MAX][MAX];
    //reset the graph
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            battle[i][j]=city[i][j];
        }
    }
    for(i=1;i<=n;i++)
    {
        visit[i]=0;
    }

    for(j=1;j<=n;j++)
    {
        battle[x][j]=INF;
        battle[j][x]=INF;
    }

    visit[x]=1;

    //find a start point
    int start;
    if(x==1) start=n;
    else start=x-1;
    visit[start]=1;

    for(i=1;i<=n;i++)
        dist[i]=battle[start][i];

    //n-2 vertices to be searched
    for(j=1;j<=n-2;j++)
    {
        int min=INF,mini=0;
        //find min cost 
        for(i=1;i<=n;i++)
        {
            if(visit[i]==0&&dist[i]<min)
            {
                min=dist[i];
                mini=i;
            }
        }
        if(min==INF&&mini==0)
        {
            cost[x]=INF;
            break;
        }
        else
        {
            cost[x]+=min;
            visit[mini]=1;
        }
        for(i=1;i<=n;i++)
        {
            if(visit[i]==0)
            {
                //set the new dist from mini to other unvisited i
                if(dist[i]>battle[mini][i])
                {
                    dist[i]=battle[mini][i];
                }
            }
        }
    }
}

void PrintResult(int max,int n,int cost[])
{
    int i,head=0;
    if(max==-1)
    {
        printf("0");
        return;
    }
    else
    {
        for(i=1;i<=n;i++)
        {
            if(cost[i]==max)
            {
                if(head==0)
                {
                    printf("%d",i);
                    head=1;
                }
                else
                {
                    printf(" %d",i);
                }
                
            }
        }
    }
}