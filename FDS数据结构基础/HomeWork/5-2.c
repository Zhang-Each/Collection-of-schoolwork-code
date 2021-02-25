#include<stdio.h>
#include<stdlib.h>

typedef struct TNode *Tree;
struct TNode{
    int value;
    Tree Left;
    Tree Right;
};

int result[1000];
int len=0;

void Print(int a[],int n);
Tree Insert(Tree X,int a);
int Compare(Tree X,Tree Y);

int main()
{
    int N;
    scanf("%d",&N);
    while(N!=0){
        int L;
        int a[11];

        scanf("%d",&L);
        Tree T=NULL;

        for(int i=0;i<N;i++){
            scanf("%d",&a[i]);
            T=Insert(T,a[i]);
        }

        for(int j=0;j<L;j++){
            Tree T1=NULL;
            int b[11];
            for(int k=0;k<N;k++){
                scanf("%d",&b[k]);
                T1=Insert(T1,b[k]);
            }

            if(Compare(T,T1)==1){
                result[len]=1;
            }
            else{
                result[len]=0;
            }
            len++;

        }
        scanf("%d",&N);
    }
    Print(result,len);
    return 0;
}

int Compare(Tree X,Tree Y)
{
    if(X==NULL&&Y==NULL){
        return 1;
    }
    else if((X==NULL&&Y!=NULL)||(X!=NULL&&Y==NULL))
    {
        return 0;
    }
    else{
        if(X->value!=Y->value) return 0;
        else{
            int a,b;
            a=Compare(X->Left,Y->Left);
            b=Compare(X->Right,Y->Right);
            return a&&b;
        }
    }
}

Tree Insert(Tree X,int a)
{
    if(X==NULL){
        X=(Tree)malloc(sizeof(struct TNode));
        X->value=a;
        X->Left=NULL;
        X->Right=NULL;
    }
    else if(a<X->value){
        X->Left=Insert(X->Left,a);
    }
    else{
        X->Right=Insert(X->Right,a);
    }
    return X;
}

void Print(int a[],int n)
{
    int i;
    for(i=0;i<len;i++){
        if(a[i]==1){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }
}