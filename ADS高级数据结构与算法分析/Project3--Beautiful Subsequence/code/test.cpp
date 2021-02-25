#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main()
{
    int i,n,m;
    scanf("%d %d",&n,&m);
    FILE *fp=fopen("testdata.txt","ab");
    fseek(fp,0,SEEK_END);
    fprintf(fp,"%d %d\n",n,m);
    srand(time(NULL));
    for(i=1;i<=n;i++){
        int a;
        a=rand()%1000;
        fprintf(fp,"%03d ",a);
    }
    fprintf(fp,"\n ");
    system("pause");
    return 0;
}