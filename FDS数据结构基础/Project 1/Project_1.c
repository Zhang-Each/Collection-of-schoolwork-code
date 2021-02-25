#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef double ElementType;

//record the start time and the end time
clock_t start1, stop1, start2, stop2, start3, stop3;

//record the run time of three functions
double duration1, duration2, duration3;

/*Algorithm1, using N−1 multiplications to compute the result directly*/
ElementType Result1(ElementType X, int N);

/*Interation Version of Algorithm 2*/
ElementType Result2(ElementType X, int N);

/*Recursion Version of Algorithm 2*/
ElementType Result3(ElementType X, int N);

int main()
{
    // X is the base number
    ElementType X;

    // N is exponent of X
    // K is how many times the function repeat
    int N, K;
    scanf("%lf%d%d", &X, &N, &K);
    
    // record the result of different algorithms
    double result1, result2, result3;
    double tick1, tick2, tick3;

    // record how long the Algorithm 1 takes
    start1 = clock();
    for(int i = 1; i <= K; i++) {
        result1 = Result1(X, N);
    }
    stop1 = clock();

    // record how long the interation version of Algorithm 2 takes
    start2 = clock();
    for(int i = 1; i <= K; i++) {
        result2 = Result2(X, N);
    }
    stop2 = clock();

    // record how long the recursion version of Algorithm 3 takes
    start3 = clock();
    for(int i = 1; i <= K; i++) {
        result3 = Result3(X, N);
    }
    stop3 = clock();

    // print the results respectively
    printf("Result1:%f\tResult2:%f\tResult3:%f\n", result1, result2, result3);

    // get the number of the total ticks that takes to finish the algorithm respectively
    tick1 = stop1 - start1;
    tick2 = stop2 - start2;
    tick3 = stop3 - start3;

    // divide ticks by CLK_TCK to get the total time respectively
    duration1 = ((double)(tick1))/CLK_TCK;
    duration2 = ((double)(tick2))/CLK_TCK;
    duration3 = ((double)(tick3))/CLK_TCK;

    // print the total ticks respectively
    printf("Tick1: %f\tTick2: %f\tTick3: %f\n", tick1, tick2, tick3);

    // print the total time respectively
    printf("Time1: %fms\tTime2: %fms\tTime3: %fms\n", duration1, duration2, duration3);
    
    system("pause");
    return 0;
}

/************************************************* 
 * Function:  Result1    
 * Description:  Algorithm1, using N−1 multiplications to compute the result directly 
 * Input:     X is the base number, N is the exponent of X 
 * Return:    the result of N th power of X
 * *************************************************/  
ElementType Result1(ElementType X, int N)
{
    double result = X;
    for(int i=1; i<=N-1; i++) {
        result *= X;
    }
    return result;
}

/************************************************* 
 * Function:  Result2    
 * Description:  Interation Version of Algorithm 2.if N is even, 
            X^N=X^(N/2)*X^(N/2); and if N is odd, 
            X^N= X^((N-1)/2)*X^((N-1)/2) *X 
 * Input:     X is the base number, N is the exponent of X 
 * Return:    the result of N th power of X
 * *************************************************/  
ElementType Result2(ElementType X, int N) 
{
    double result = 1; 
    double x=X;
    while(N>0) {
        if(N%2 == 1) result = result*x;
        N = N/2;
        x = x*x;
    }
    return result;
}

/************************************************* 
 * Function:  Result3    
 * Description: Recursion Version of Algorithm 2.if N is even, 
            we will return  Result3(X,N/2)*Result3(X,N/2); and if
            N is odd, we will return  Result3(X,(N-1)/2)*Result3(X,(N-1)/2)*X
 * Input:     X is the base number, N is the exponent of X 
 * Return:    the result of N th power of X
 * *************************************************/ 
ElementType Result3(ElementType X, int N)
{
    if(N == 1) return X;
    if(N%2 == 0) return Result3(X,N/2)*Result3(X,N/2);
    else return Result3(X,(N-1)/2)*Result3(X,(N-1)/2)*X;
}