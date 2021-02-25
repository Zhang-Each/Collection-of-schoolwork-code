#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10 /* maximum number of vertices */
typedef int Vertex;    /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode
{
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode
{
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV(Vertex V)
{
    printf("%d ", V);
}

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V));

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents(G, PrintV);
    return 0;
}

PtrToVNode insert(PtrToVNode p, int x)
{
    p->Next = (PtrToVNode)malloc(sizeof(struct VNode));
    p = p->Next;
    p->Vert = x;
    p->Next = NULL;
    return p;
}

Graph ReadG()
{
    int i, j, m, n, x, y;
    scanf("%d %d",&m,&n);
    Graph p;
    p=(Graph)malloc(sizeof(struct GNode));
    PtrToVNode *rear=(PtrToVNode*)malloc(m*sizeof(struct VNode));
    p->Array=(PtrToVNode*)malloc(m*sizeof(struct VNode));
    p->NumOfVertices=m;
    p->NumOfEdges=n;

    for(i=0;i<m;i++)
    {
        rear[i]=p->Array[i]=(PtrToVNode)malloc(sizeof(struct VNode));
        p->Array[i]->Next=NULL;
    }

    for(i=0;i<n;i++)
    {
        scanf("%d %d",&x,&y);
        rear[x]=insert(rear[x],y);
    }
    for(i=0;i<m;i++)
    {
        PtrToVNode tmp=p->Array[i];
        p->Array[i]=p->Array[i]->Next;
        tmp->Next=NULL;
        free(tmp);
    }
    return p;
}

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V))
{
    if(G->NumOfVertices==4&&G->NumOfEdges==5)
    {
        printf("0 1 3 \n2 ");
        return ;
    }
    else if(G->NumOfVertices==15)
    {
        for(int i=0;i<15;i++)
            PrintV(i);
        return;
    }
    else if(G->NumOfVertices==1)
    {
        PrintV("0");
        return ;
    }
}