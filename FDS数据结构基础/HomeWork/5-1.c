#include <stdio.h>
#include <stdlib.h>

typedef struct TNode *BinTree;
struct TNode{
    int Key;
    BinTree Left;
    BinTree Right;
};

BinTree BuildTree(); /* details omitted */
int CheckBST ( BinTree T, int K );

int main()
{
    BinTree T;
    int K, out;

    T = BuildTree();
    scanf("%d", &K);
    out = CheckBST(T, K);
    if ( out < 0 )
        printf("No.  Height = %d\n", -out);
    else
        printf("Yes.  Key = %d\n", out);

    return 0;
}

int a[100],len=0;
void Inorder(BinTree T)
{
    if(T!=NULL){
        Inorder(T->Left);
        a[len]=T->Key;
        len++;
        Inorder(T->Right);
    }
    return;
}

int Getheight(BinTree T)
{
    if(T==NULL){
        return 0;
    }
    int x,y;
    x=getheight(T->Right);
    y=getheight(T->Left);
    if(x>y){
        return x+1;
    }
    else return y+1;
    
}

int IsBST(BinTree T)
{
    int j;
    Inorder(T);
    for(j=1;j<len;j++)
    {
        if(a[j-1]>=a[j]){//中序遍历产生的数列应该是递增的
            return 0;
        }
    }
    return 1;
}

int CheckBST ( BinTree T, int K )
{
    int j,h;
    h=Getheight(T); 
    if(IsBST(T)==1){ //如果是二叉搜索树则返回第K大的数
        return a[len-K];
    }
    else return -h;
}