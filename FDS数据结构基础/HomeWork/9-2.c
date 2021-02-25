#include <stdio.h>
#include <stdlib.h>

//typedef enum {false, true} bool;
#define INFINITY 1000000
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */
typedef int WeightType;

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph ReadG(); /* details omitted */

void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S );

int main()
{
    int dist[MaxVertexNum], path[MaxVertexNum];
    Vertex S, V;
    MGraph G = ReadG();

    scanf("%d", &S);
    ShortestDist( G, dist, path, S );

    for ( V=0; V<G->Nv; V++ )
        printf("%d ", dist[V]);
    printf("\n");
    for ( V=0; V<G->Nv; V++ )
        printf("%d ", path[V]);
    printf("\n");

    return 0;
}
MGraph ReadG()
{
    MGraph G;
    G=(MGraph)malloc(sizeof(struct GNode));
    int i,j,k,len;
    scanf("%d %d",&G->Nv,&G->Ne);
    for(i=0;i<G->Nv;i++){
        for(j=0;j<G->Nv;j++){
            G->G[i][j]=INFINITY;
        }
    }
    for(k=0;k<G->Ne;k++){
        scanf("%d %d %d",&i,&j,&len);
        G->G[i][j]=len;
    }
    /*show the graph
    for(i=0;i<G->Nv;i++){
        for(j=0;j<G->Nv;j++){
            if(G->G[i][j]==INFINITY){
                printf("0 ");
            }
            else printf("%d ",G->G[i][j]);
        }
        printf("\n");
    }
    */
   return G;
}

void Init(MGraph Graph, int dist[], int path[], Vertex S)
{
    int i;
    for(i=0;i<Graph->Nv;i++){
        dist[i]=INFINITY;
        path[i]=-1;
    }
    dist[S]=0;
}

void ShortestDist( MGraph Graph, int dist[], int path[], Vertex S )
{
    int i,known[MaxVertexNum]={0};
    Init(Graph,dist,path,S);
    for(;;){
        Vertex v,w;
        int min=INFINITY;
        v=Graph->Nv;
        for(i=0;i<Graph->Nv;i++){
            if(!known[i]){
                if(dist[i]<min){
                    v=i;
                    min=dist[i];
                }
            }
        }
        if(v==Graph->Nv) break;
        known[v]=1;
        for(w=0;w<Graph->Nv;w++){
            if(Graph->G[v][w]<INFINITY){
                int len=Graph->G[v][w];
                if(dist[w]>len+dist[v]&&known[w]==0){
                    dist[w]=len+dist[v];
                    path[w]=v;
                }
            }
        }
    }
    int k=0;
    while(k<Graph->Nv){
        if(dist[k]==INFINITY){
            dist[k]=-1;
            path[k]=-1;
        }
        k++;
    }
}