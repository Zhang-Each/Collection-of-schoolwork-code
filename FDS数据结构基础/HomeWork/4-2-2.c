#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode *Tree;
struct TreeNode {
    int Element;
    Tree  Left;
    Tree  Right;
    Tree  Father;
    int flag;
};
int i=0;
void Postorder(Tree head);
int main(void)
{
    int i,n,data;
    char order[6];
    Tree head, p1,p2;
    head = p1 = NULL;
    scanf("%d",&n);
    for(i=0;i<2*n;i++)
    {
        scanf("%s",order);
        if(strcmp(order,"Push")==0)
        {
            scanf("%d",&data);
            p2=(struct TreeNode*)malloc(sizeof(struct TreeNode));
            p2->Element=data;
            p2->flag=0;
            p2->Left=NULL;
            p2->Right=NULL;
            p2->Father=NULL;;
            if(!head)
                head=p1=p2;
            else
            {
                if(p1->flag==0)
                {
                    p1->Left=p2;
                    p2->Father=p1;
                    p1=p2;
                }
                else
                {
                    p1->Right=p2;
                    p2->Father=p1;
                    p1=p2;
                }
            }
            
        }
        else
        {
            if(p1->Left==NULL&&p1->flag==0)
                p1->flag=1;
            else
            {
                while(p1->Father->flag==1)
                {
                    p1=p1->Father;
                }
                p1= p1->Father;
                p1->flag=1;
            }
            
        }
    }
    Postorder(head) ;
    return 0;

}
void Postorder(Tree head)
{
    if( head ) {
        Postorder( head->Left );
        Postorder( head->Right );
        if(i==0)
        {
            printf("%d", head->Element);
            i=1;
        }
        else
            printf(" %d", head->Element);
    }
}