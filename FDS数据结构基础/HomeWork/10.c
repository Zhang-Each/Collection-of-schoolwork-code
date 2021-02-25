#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1000
#define INF 100000

int G[MAX][MAX];
char id[MAX][4];
int len=0,result;
int visit[MAX],q[MAX],pre[MAX],rear,front;
int search(int s,int e,int n);
int maxflow(int s,int e,int n);

int main()
{
    int i,j,n;
    char x[4],y[4];
    scanf("%s %s %d",x,y,&n);
    strcpy(id[0],x);
    strcpy(id[1],y);
    len=2;
    for(i=0;i<n;i++)
    {
        int length;
        scanf("%s %s %d",x,y,&length);
        int idx=-1,idy=-1;
        for(j=0;j<len;j++)
        {
            if(strcmp(id[j],x)==0)
            {
                idx=j;
                break;
            }
        }
        if(idx==-1){
            idx=len;
            strcpy(id[len++],x);
        }
        for(j=0;j<len;j++)
        {
            if(strcmp(id[j],y)==0)
            {
                idy=j;
                break;
            }
        }
        if(j==len){
            idy=len;
            strcpy(id[len++],y);
        }
        G[idx][idy]=length;
    }
    result=maxflow(0,1,len);
    printf("%d",result);
    return 0;
}

int minlen=INF;
int maxflow(int s,int e,int n)
{
    int i,result=0;
    while(1)
    {
        if(search(s,e,n)==0)
            return result;
        for(i=e;i!=s;i=pre[i])
            if(G[pre[i]][i]<minlen)
                minlen=G[pre[i]][i];
        for(i=e;i!=s;i=pre[i])
        {
            G[pre[i]][i]-=minlen;
            G[i][pre[i]]+=minlen;
        }
        result+=minlen;
    }
    return result;
}

int search(int s,int e,int n)
{
    int v,i;
    rear=0;
    front=0;
    memset(visit,0,sizeof(visit));
    q[rear]=s;
    rear++;
    visit[s]=1;
    while(rear-front!=0)
    {
        v=q[front];
        front++;
        for(i=0;i<n;i++)
        {
            if(visit[i]==0&&G[v][i]!=0)
            {
                q[rear]=i;
                rear++;
                visit[i]=1;
                pre[i]=v;
                if(i==e){
                    return 1;
                }
            }
        }
    }
    return 0;
}