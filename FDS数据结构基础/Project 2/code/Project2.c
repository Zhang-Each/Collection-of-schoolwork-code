#include<stdio.h>
#include<stdlib.h>

#define INFINITY 1000000 /*INFINITY means Station A and Station B aren't connected.*/
#define MaxStationNum 501 /*The maximum number of the stations.*/

typedef int WeightType;
typedef struct GNode *PtrToGNode;

/*The data structure for the graph.*/
struct GNode {
    int Cmax;   // the maximum capacity of each station
    int N;      // the total number of stations
    int Sp;     // the index of the problem station 
    int M;      // the number of roads
    int Time[MaxStationNum][MaxStationNum];
    WeightType Capacity[MaxStationNum];
};

typedef PtrToGNode Graph;

void Init();
void DFS(int current);
void CheckStack();
void ResetPath();
void PrintResult();
void CaculateTimeAndBike();

int Known[MaxStationNum]; /*To mark if we have passed the i-th station: Known[i] equals 0 when we haven't passed the i-th station, while Known[i] equals 1 when we have passed the i-th station.*/
int Stack[MaxStationNum + 3]; /*The path we're dealing with.*/
/*'Stack[MaxStationNum]' means the time we need to reach PBMC.*/
/*'Stack[MaxStationNum + 1]' means the bikes we need to take from PBMC.*/
/*'Stack[MaxStationNum + 2]' means the bikes we need to take back to PBMC.*/
int Path[MaxStationNum + 3]; /*The most-required path among the previous paths from PBMC to the problem station.*/
/*'Path[MaxStationNum]' means the time we need to reach PBMC.*/
/*'Path[MaxStationNum + 1]' means the bikes we need to take from PBMC.*/
/*'Path[MaxStationNum + 2]' means the bikes we need to take back to PBMC.*/
int flag; /*'flag' is to verify if the array is defined.*/
int top; /*The index of the toppest element in the array named 'Stack'.*/
Graph G;

int main()
{
    /*Initing the graph and the global variables*/
    Init();

    /*Using the method of depth-first-search to find the 
    required path and store it to the array named 'Path'.*/
    DFS(0);
    
    /*To print the final result.*/
    PrintResult();
    system("pause");
    return 0;
}

/*This function is to init the graph and the global variables.*/
void Init()
{
    G = (Graph)malloc(sizeof(struct GNode));
    scanf("%d %d %d %d", &(G->Cmax), &(G->N), &(G->Sp), &(G->M));
    int i, j, k;
    G->Capacity[0] = 0;
    for(i = 1; i <= G->N; i++) scanf("%d", &(G->Capacity[i]));
    /* initialization: set the time spent per edge INFINITY*/
    for(i = 0; i <= G->N; i++) {
        for(j = 0; j <= G->N; j++) {
            G->Time[i][j] = INFINITY;
            if(i == j) G->Time[i][j] = 0;
        }
    }
    /* input the time spent per edge*/
    for(i = 1; i <= G->M; i++) {
        int StationA, StationB, time;
        scanf("%d %d %d", &StationA, &StationB, &time);
        G->Time[StationA][StationB] = time;
        G->Time[StationB][StationA] = time;
    }
    /* initialization: Known[k],Stack[k],Path[k]*/
    for(k = 0; k < MaxStationNum; k++) {
        Known[k] = 0;
        Stack[k] = -1;
        Path[k] = -1;
    }
    Path[MaxStationNum] = 0;
    Path[MaxStationNum + 1] = 0;
    Path[MaxStationNum + 2] = 0;
    top = -1;
    flag = 0;
}

/*This function is to use the method of depth-first-search
  to find the most required path to solve the problem     */
void DFS(int current)
{
    Known[current] = 1;
    Stack[++top] = current;
    /*Stack[MaxStationNum] is to save the time cost.*/
    if(current == 0) Stack[MaxStationNum] = 0;
    else Stack[MaxStationNum] += G->Time[Stack[top - 1]][Stack[top]];
    /*To judge if the current station is the problem station. If it's the problem station, check the current path with the array 'Path' and pop the top element out.*/
    if(current == G->Sp) {
        CheckStack();
        Stack[MaxStationNum] -= G->Time[Stack[top - 1]][Stack[top]];
        top--;
        Known[current] = 0;
        return;
    }
    /*To improve our algorithm, we add this piece of codes: If we have stored a
      qualified path in array 'Path', compare the current time cost with the path
      in array 'Path'. If its time cost is already larger than the path in array
      'Path', quit the current path and search for the next qualified path.*/
    if(flag == 1 && Stack[MaxStationNum] > Path[MaxStationNum]) {
        if(current != 0) Stack[MaxStationNum] -= G->Time[Stack[top - 1]][Stack[top]];
        top--;
        Known[current] = 0;
        return;
    }
    int i;
    /* Depth first search:search every road leading to the station */
    for(i = 0; i <= G->N; i++) {
        if(Known[i] == 0 && G->Time[current][i] < INFINITY) {
            DFS(i);
        }
    }
    /* Flashing back */
    Stack[MaxStationNum] -= G->Time[Stack[top - 1]][Stack[top]];
    top--;
    Known[current] = 0;
}

/*This function is to find the better path by comparing from 3 angles,the
  time we need to reach PBMC, the number of the bikes we need to take from
  PBMC and the number of the bikes we need to take back to PBMC, respectively.*/
void CheckStack()
{
    /*For the path stored in the 'Stack', to caculate the time cost,
      the number of bikes it needs to tack from and bring back to PBMC*/
    CaculateTimeAndBike();
    if(flag == 0) {
        ResetPath();
        flag = 1;
    }
    /*Firstly, we need to compare the time cost.*/    
    else if(Path[MaxStationNum] > Stack[MaxStationNum]) ResetPath();
    else if(Path[MaxStationNum] == Stack[MaxStationNum]) {
    /*If such a path is not unique, output the one that requires 
      minimum number of bikes that we must take back to PBMC.*/
        if(Path[MaxStationNum + 1] > Stack[MaxStationNum + 1]) ResetPath();
        else if(Path[MaxStationNum + 1] == Stack[MaxStationNum + 1]) {
            if(Path[MaxStationNum + 2] > Stack[MaxStationNum + 2]) ResetPath();
        }  
    }
}

/*This function is to reset the array 'Path' when we find a better path.*/
void ResetPath()
{
    int i;
    Path[MaxStationNum] = Stack[MaxStationNum];
    Path[MaxStationNum + 1] = Stack[MaxStationNum + 1];
    Path[MaxStationNum + 2] = Stack[MaxStationNum + 2];
    for(i = 0; i <= top; i++) Path[i] = Stack[i];
}

/*This function is to caclulate the time we need to reach PBMC,the number
  of the bikes we need to take from PBMC and the number of the bikes we 
  need to take back to PBMC if we choose the the path stored in array 'Stack'.*/
void CaculateTimeAndBike()
{
    /*The variable named 'temp' is used to save the bikes we take with us after passing the current station.*/
    int i, temp = 0;
    /*Init the the time cost, the number of bikes it needs to tack from and bring back to PBMC.*/
    Stack[MaxStationNum] = 0;
    Stack[MaxStationNum + 1] = 0;
    Stack[MaxStationNum + 2] = 0;
    for(i = 0; i <= top; i++) {
        if(i < top) Stack[MaxStationNum] += G->Time[Stack[i]][Stack[i + 1]];
        if(i > 0) {
            /*If the bikes in the Stack[i] are more than one half of the max capacity.*/
            if(G->Capacity[Stack[i]] >= G->Cmax / 2) 
                temp += (G->Capacity[Stack[i]] - G->Cmax / 2);
            /*If the bikes in the Stack[i] are less than one half of the max capacity.*/
            else if(G->Capacity[Stack[i]] < G->Cmax / 2) {
                if(temp >= G->Cmax / 2 - G->Capacity[Stack[i]]) temp -= (G->Cmax / 2 - G->Capacity[Stack[i]]);
                else {
                    Stack[MaxStationNum + 1] += (G->Cmax / 2 - G->Capacity[Stack[i]] - temp);
                    temp = 0;
                }
            }
        }
    }
    /*After passing the last station, variable 'temp' equals to the number of bikes we need to take bake to PBMC.*/
    Stack[MaxStationNum + 2] = temp;
}

/*This function is to print the final result.*/
void PrintResult()
{
    /*To print the bikes we need to take from PBMC.*/
    printf("%d ", Path[MaxStationNum + 1]);
    /*To print the path.*/
    int i = 0;
    for(i = 0; ; i++) {
        printf("%d", Path[i]);
        if(Path[i] != G->Sp) printf("->");
        else {
            printf(" ");
            break;
        }
    }
    /*To print the bikes we need to take back to PBMC.*/
    printf("%d", Path[MaxStationNum + 2]);
}