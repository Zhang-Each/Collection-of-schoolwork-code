#include<stdio.h>
#define MAX 10001
struct record
{
    int id;
    int time;
    int state;
};
char car[MAX][10];
int cars=0;

int main()
{
    int i,j,N,K;
    scanf("%d %d",&N,&K);
    for(i=0;i<N;i++)
    {
        char plate[11],status[3];
        int h,m,s,in;
        scanf("%s %d:%d:%d %s",plate,&h,&m,&s,status);
        if(status[0]=='i') in=1;
        else in=0;
        printf("%s %d %d %d %d\n",plate,h,m,s,in);
    }
    return 0;
}