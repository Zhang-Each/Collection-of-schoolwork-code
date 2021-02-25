#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};

Tree BuildTree(); /* details omitted */

int Isomorphic( Tree T1, Tree T2 );

int main()
{
    Tree T1, T2;
    T1 = BuildTree();
    T2 = BuildTree();
    printf("%d\n", Isomorphic(T1, T2));
    return 0;
}

int IsEmpty(Tree X)
{
    int result=0; //if the tree is empty, return 1, else return 0;
    if(X==NULL){
        result=1;
    }
    return result;
}

int Isomorphic( Tree T1, Tree T2 )
{
    int x,y;
    x=IsEmpty(T1);
    y=IsEmpty(T2);
    if(x==1||y==1){
        if(x==1&&y==0){
            return 0; 
        }
        else if(x==0&&y==1){
            return 0;
        }//if only one tree is empty, then they are not Isomorphic
        else if(x==1&&y==1){
            return 1;
            //two trees are both empty,then they are Isomorphic
        }
    }
    else{ //both of the tree is not empty
        if(T1->Element==T2->Element){ //compare the element first
            int L_L,R_R,R_L,L_R;
            L_L=Isomorphic(T1->Left,T2->Left);
            R_R=Isomorphic(T1->Right,T2->Right);
            L_R=Isomorphic(T1->Left,T2->Right);
            R_L=Isomorphic(T1->Right,T2->Left);

            if(L_L*R_R==1){
                return 1;
            }
            else if(L_R*R_L==1){
                return 1;
            }
            else{
                return 0;
            }
        }
        else if(T1->Element!=T2->Element){
            return 0;
        }
    }
} 