#include<stdio.h>
#include<stdio.h>

int N,M,S;//N nodes in a tree,M non-leaf nodes,S the weight
void PrintTree();
void PathSearch(int index,int num,int sum);
struct node{
    int weight;
    int numberofson;
    int son[100];
};

struct node tree[101];
int path[101];

int main()
{
    int i,j,son[100];
    scanf("%d %d %d",&N,&M,&S);

    for(i=0;i<N;i++){
        scanf("%d",&tree[i].weight);
        tree[i].numberofson=0;
    }

    for(i=0;i<M;i++){
        int id,number;
        scanf("%d %d",&id,&number);
        tree[id].numberofson = number;
        for(j=0;j<number;j++){
            scanf("%d",&son[j]);
        }
        for(int k=0;k<number-1;k++){ //bubble sort to make the son's weight not increasing
            for(int l=0;l<number-1-k;l++){
                if(tree[son[l]].weight<tree[son[l+1]].weight){
                    int temp=son[l];
                    son[l]=son[l+1];
                    son[l+1]=temp;
                }
            }
        }
        for(j=0;j<number;j++){
            tree[id].son[j]=son[j];
        }
    }
    PathSearch(0,1,tree[0].weight);
    //PrintTree();
    return 0;
}
void PathSearch(int index,int num,int sum)
{
    int i;
    if(sum>S){
        return;
    }
    if(sum==S){
        if(tree[index].numberofson!=0){
            return;
        }
        for(i=0;i<num;i++){
            if(i==0){
                printf("%d",tree[path[i]].weight);
            }
            else{
                printf(" %d",tree[path[i]].weight);
            }
        }
        printf("\n");
        return;
    }
    for(i=0;i<tree[index].numberofson;i++){
        int newnode=tree[index].son[i];
        path[num]=newnode;
        PathSearch(newnode,num+1,sum+tree[newnode].weight);
    }

}
void PrintTree() //a test funciton to print the node of the trees and their sons
{
    int i,j;
    for(i=0;i<N;i++){
        printf("%d %d    son:",tree[i].weight,tree[i].numberofson);
        for(j=0;j<tree[i].numberofson;j++){
            printf(" %d",tree[i].son[j]);
        }
        printf("\n");
    }
}