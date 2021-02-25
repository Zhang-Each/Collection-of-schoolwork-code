#include <stdio.h>
#include <stdlib.h>

// The max size of test data
#define MAX 1000
#define MAXNUM 100000

// The graph relation of the fruits
int fruit[MAX][MAX] = {0};
// The max number of safe fruit after this fruit
int Maxnumber[MAX];
// a stack that will be used to store the 'safe fruit' of fruit i
int s[MAX][MAX];
// a matrix to store the unsafe fruits of each fruit
// unsafelen is the length of each fruit's unsafe list
int unsafe[MAX][MAX], unsafelen[MAX] = {0};
// temp[] is The possible combination of safe fruits in the backtrack
// path[] is the final result 
// templen and pathlen are the length of the two array
int temp[MAX], path[MAX];
int templen = 0, pathlen = 0;
// price[] store the cost of each kind of fruit
// tmp is the possible totoal cost of a safe fruit combination, and cost is the final result
// number is the final amount of fruit 
int price[MAX], tmp, cost, number = 0;

// the main function to backtracking
void dfs(int n, int num, int step);
// a self-definition function to compare 2 integers
int comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    // n is the number of pairs of unsafe fruit
    // m is the number of fruit you can buy
    int m, n, a, b;
    int i, j;
    // read in m and n 
    scanf("%d %d", &n, &m);

    for (i = 0; i < n; i++)
    {
        // read in the paris of unsafe fruits
        scanf("%d %d", &a, &b);
        unsafe[a][unsafelen[a]++] = b;
    }
    // make 2 array to store the fruit you can buy
    int list1[MAX], list2[MAX];
    for (i = 0; i < MAX; i++)
    {
        list1[i] = MAXNUM;
        list2[i] = MAXNUM;
    }

    // you should learn that not all the fruits in the unsafe pairs can be bought from store.
    // So we need to give them new lables, this time we remark the fruit in the order of input from 0 to m-1.
    // and we use 2 arrays to store the corresponding relations between its origin lable and new lable
    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &a, &price[i]);
        list2[i] = a;
        list1[a] = i;
    }

    // now we construct a graph relation of the m kinds of fruits
    // fruit[i][j] = 0 means they can eat safely one by one 
    for (i = 0; i < m; i++)
    {
        fruit[i][i] = 1;
        // travle around the unsafe list of each fruit to mark all the fruit which can't be eaten together
        for (int j = 0; j < unsafelen[list2[i]]; j++)
        {
            int k = unsafe[list2[i]][j];
            // keep all the fruit in the graph are in the kind 0 to m-1
            if (list1[k] < m)
                fruit[i][list1[k]] = fruit[list1[k]][i] = 1;
        }
    }

    /* a period of test code to print the graph
    for(i=0;i<m;i++){
		for(j=0;j<m;j++){
			cout<<fruit[i][j]<<" ";
		}
		cout<<endl;
	}
    */

    //traverse all the fruit to find a max combination of safe fruit using dfs
    for (i = m - 1; i >= 0; i--)
    {
        // cout store the number of safe fruit of each fruit[i]
        int count = 0;
        // push all the safe fruit of fruit[i] in the stack
        for (j = i + 1; j < m; j++)
        {
            if (!fruit[i][j])
                s[0][count++] = j;
        }

        //start the backtracking, first push the node i into the temp_path
        temp[templen++] = i;
        tmp += price[i];
        //solve the problem using dfs, m is the number of fruit 
        //and count is the number of safe fruit in the stack
        dfs(m, count, 1);
        templen--;
        tmp -= price[i];
        Maxnumber[i] = number;
    }
    // change the new lable into its origin lable
    for (i = 0; i < pathlen; i++)
        path[i] = list2[path[i]];
    // use the C library function qsort in <stdlib.h> to sort the fruits in increasing order
    qsort(path, pathlen, sizeof(int), comp);

    // print the answers in a proper format.
    printf("%d\n", number);
    for (i = 0; i < pathlen; i++)
    {
        if (!i)
            printf("%03d", path[i]);
        else
            printf(" %03d", path[i]);
    }
    printf("\n");
    printf("%d", cost);
    system("pause");
    return 0;
}
//the most significant function to implement the backtracking algorithm
// n: the number of different fruit
// num: the number of safe fruit
// step: the level of backtracking
void dfs(int n, int num, int step)
{
    // when a backtracking finished
    if (num == 0)
    {
        // if find a better result with more fruit or less cost
        if (step > number || (step == number && tmp < cost))
        {
            //update the result and return, finish one backtracking
            cost = tmp;
            number = step;
            pathlen = templen;
            for (int i = 0; i < templen; i++)
            {
                path[i] = temp[i];
            }
        }
        return;
    }
    int i;
    // traverse the fruits in the 'safe stack' to begin the next level of backtracking
    for (i = 0; i < num; i++)
    {
        // count is the number of safe fruit
        int j, k, count = 0;
        k = s[step - 1][i];
        // special conditions that can end the backtracking early, prunning
        if (step + Maxnumber[k] < number)
            return;
        //repeat the method of begin a backtracking by find all the safe fruits 
        for (j = i + 1; j < num; j++)
        {
            if (!fruit[k][s[step - 1][j]])
            {
                s[step][count++] = s[step - 1][j];
            }
        }
        // start a new backtracking
        temp[templen++] = k;
        tmp += price[k];   
        // the level will up 1   
        dfs(n, count, step + 1);
        tmp -= price[k];
        templen--;
    }
}