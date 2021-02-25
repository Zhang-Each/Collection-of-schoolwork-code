#include <stdio.h>
#include <stdlib.h>

typedef enum { true, false, maybe } Keys;
typedef Keys ElementType;

void Read( ElementType A[], int N ); /* details omitted */

void MySort( ElementType A[], int N );

void PrintA( ElementType A[], int N )
{
    int i, k;

    k = i = 0;
    for ( ; i<N && A[i]==false; i++ );
    if ( i > k )
        printf("false in A[%d]-A[%d]\n", k, i-1);
    k = i;
    for ( ; i<N && A[i]==maybe; i++ );
    if ( i > k )
        printf("maybe in A[%d]-A[%d]\n", k, i-1);
    k = i;
    for ( ; i<N && A[i]==true; i++ );
    if ( i > k )
        printf("true in A[%d]-A[%d]\n", k, i-1);
    if ( i < N )
        printf("Wrong Answer\n");
}

int main()
{
    int N;
    ElementType *A;

    scanf("%d", &N);
    A = (ElementType *)malloc(N * sizeof(ElementType));
    Read( A, N );

    MySort( A, N );
    PrintA( A, N );
    return 0;
}

void Read( ElementType A[], int N )
{
    int i,a;
    for(i=0;i<N;i++)
    {
        scanf("%d",&a);
        if(a==0) A[i]=true;
        else if(a==1) A[i]=false;
        else A[i]=maybe;
    }
}

void MySort( ElementType A[], int N )
{
    int a,b,c,i;
    a=0;
    b=0;
    c=0;
    for(i=0;i<N;i++)
    {
        if(A[i]==true) a++;
        else if(A[i]==false) b++;
        else c++;
    }
    for(i=0;i<b;i++) A[i]=false;
    for(i=b;i<b+c;i++) A[i]=maybe;
    for(i=b+c;i<b+c+a;i++) A[i]=true;
}