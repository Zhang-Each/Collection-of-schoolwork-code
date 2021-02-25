#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}

int IsEmpty(int rear,int front)
{
    if(rear<front){
        return 0;
    }
    else return 1;
}

bool IsTopSeq( LGraph Graph, Vertex Seq[] )
{
    PtrToAdjVNode x;
    int Indegree[MaxVertexNum+1]={0};
    for(int i=0;i<Graph->Nv;i++){
        x=Graph->G[i].FirstEdge;
        while(x!=NULL){
            Indegree[x->AdjV]++;
            x=x->Next;
        }
    }
    int Queue[MaxVertexNum+2],head,tail,k;
    head=-1;
    tail=-1;
    k=0;
    while(k<Graph->Nv){
        tail++;
        Queue[tail]=Seq[k]-1;
        k++;
    }
    while(IsEmpty(head,tail)==0){
        head++;
        if(Indegree[Queue[head]]!=0){
            return false;
        }
        x=Graph->G[Queue[head]].FirstEdge;
        while(x!=NULL){
            Indegree[x->AdjV]--;
            x=x->Next;
        }
    }
    return true;
    int y=1;
    
}