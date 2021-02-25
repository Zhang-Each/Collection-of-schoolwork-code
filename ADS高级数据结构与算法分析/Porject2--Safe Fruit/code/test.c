#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int main()
{
    int i,n,m;
    scanf("%d %d",&n,&m);
    FILE *fp=fopen("bigtestdata.txt","ab");
    fseek(fp,0,SEEK_END);
    fprintf(fp,"%d %d\n",n,m);
    srand(time(NULL));
    for(i=1;i<=n+m;i++){
        int a,b;
        a=rand()%1000;
        b=rand()%1000;
        if(i<=n){
            while(a==b){
                a=rand()%1000;
                b=rand()%1000;
            }
            fprintf(fp,"%03d %03d\n",a,b);
        }
        else{
            fprintf(fp,"%03d %d\n",a,b);
        }
    }
    system("pause");
    return 0;
}