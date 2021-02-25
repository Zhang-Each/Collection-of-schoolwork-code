#include<stdio.h>
int result[1001];
int t=1;
void Print(int n);
void Bubblesort(int n,int x[]);
void Inorder(int k,int x[],int n);
int main()
{
    int n,i,j;
    int number[1001]={-1};
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&number[i]);
    }
    Bubblesort(n,number);
    Inorder(1,number,n);
    Print(n);
    return 0;
}

void Bubblesort(int n,int x[])
{
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=1;j<n-i;j++){
            if(x[j]>x[j+1]){
                int temp=x[j];
                x[j]=x[j+1];
                x[j+1]=temp;
            }
        }
    }
}

void Print(int n)
{
    int i;
    for(i=1;i<=n;i++){
        if(i==1){
            printf("%d",result[i]);
        }
        else{
            printf(" %d",result[i]);
        }
    }
}

void Inorder(int k,int x[],int n)
{
    if(k>n){
        return;
    }
    int k1=2*k,k2=2*k+1;
    Inorder(k1,x,n);
    result[k]=x[t];
    t++;
    Inorder(k2,x,n);
}