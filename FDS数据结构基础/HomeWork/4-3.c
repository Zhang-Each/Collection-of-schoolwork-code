#include<stdio.h>
#include<stdlib.h>

int post[50],in[50];
int tree[50][50]={0};//the element of tree
int node[50]={0};//the number of nodes of each level

void CreateTree(int x,int y,int z,int depth);
void PrintTree(int k);

int main()
{
    int i,j,k=0,n;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&in[i]);
    }
    for(j=0;j<n;j++){
        scanf("%d",&post[j]);
    }

    CreateTree(0,n-1,n-1,0);
    while(node[k]!=0){
        k++;
    }
    PrintTree(k);
    return 0;
}

void PrintTree(int k)
{
    int i,j;
    printf("%d",tree[0][0]);
    for(i=1;i<k;i++){
        if(i%2==1){
            for(j=0;j<node[i];j++){
                printf(" %d",tree[i][j]);
            }
        }
        else{
            for(j=node[i]-1;j>=0;j--){
                printf(" %d",tree[i][j]);
            }
        }
    }
}

void CreateTree(int x,int y,int z,int depth)
{
    if(x>y) return;
    int l=x;
    tree[depth][node[depth]]=post[z];
    node[depth]++;
    while(in[l]!=post[z]){
        l++;
    }
    depth++;
    z--;
    CreateTree(x,l-1,z-y+l,depth);
    CreateTree(l+1,y,z,depth);
}