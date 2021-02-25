#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int pre[50],in[50],stack[50];
int post[50];

void CreatePost(int x,int y,int z,int n);
void PrintPost(int m[],int n);

int main()
{
    char op[5];
    int n,num,countofpop=0;
    int i,j,k;
    scanf("%d",&n);
    i=0;
    j=0;
    k=0;
    while(countofpop<n){
        scanf("%s",op);
        if(strcmp(op,"Push")==0){
            scanf("%d",&num);
            pre[i]=num;
            i++;
            stack[k]=num;
            k++;
        }
        else if(strcmp(op,"Pop")==0){
            getchar();
            countofpop++;
            k--;
            in[j]=stack[k];
            j++;
        }
    }
    
    CreatePost(0,0,0,n);
    PrintPost(post,n);
    return 0;
}

void PrintPost(int m[],int n)//print the result
{
    int count=0,i;
    for(i=0;i<n;i++){
        if(count==0){
            printf("%d",m[i]);
            count=1;
        }
        else{
            printf(" %d",m[i]);
        }
    }
}

void CreatePost(int x,int y,int z,int n)//to create the post traversal of the input
{
    int num,left,right;
    if(n==0){
        return;
    }
    else if(n==1){
        post[z]=pre[x];
        return;
    }
    num=pre[x];
    post[n-1+z]=pre[x];
    x++;
    left=0;
    while(in[y+left]!=num){
        left++;
    }
    right=n-left-1;
	CreatePost(x,y,z,left);
    x+=left;
    y+=left+1;
    z+=left;
	CreatePost(x,y,z,right);
}