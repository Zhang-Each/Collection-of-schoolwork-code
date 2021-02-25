#include<stdio.h>

void Print(int x[],int y)
{
    int i;
    for(i=0;i<y;i++){
        if(x[i]){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
    }
}

int compare(int x,int y)
{
    if(x==y) return 1;
    else return 0;
}

int main()
{
    int result[1000],len=0;// to memory the results:YES or NOT
    int M,N,K; //the information that has told you
    int stack[1001],top,num,x,i,j;
    scanf("%d %d %d",&M,&N,&K);
    stack[M]=-1;// set the stack

    for(i=0;i<K;i++){
        top=-1;
        result[len]=1;
        num=1;
        if(M>0){
            top++;
            stack[top]=num;
        }
        else{
            printf("NO\n");
        }
        for(j=0;j<N;j++){
            scanf("%d",&x);
            if(result[len]==1){
                while(top<=M-2&&num<=N-1&&(stack[top]<x||top==-1)){
                    num++;
                    top++;
                    stack[top]=num;
                }
                if(compare(x,stack[top])){
                    top=top-1;
                }
                else{
                    result[len]=0;
                }
            }
        }
        len++; 
    }
    Print(result,len);
    return 0;
}