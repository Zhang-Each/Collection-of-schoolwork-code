#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}
int overflow(int x,int y,int n,int i,int len)
{
    if(x<n&&y<n)
        if(x<i+len&&y<i+2*len) return 0;
    return 1;
}
void merge_pass( ElementType list[], ElementType sorted[], int N, int length )
{
    int i,j;
    for(i=0;i<N;i+=2*length)
    {
        int x,y,z;
        x=i;
        y=i+length;
        z=x;
        while(!overflow(x,y,N,i,length))
        {
            if(list[x]<list[y]) sorted[z++]=list[x++];
            else sorted[z++]=list[y++];
        }
        if(x<i+length)
            while(x<i+length) sorted[z++]=list[x++];
        else if(y<i+2*length)
            while(y<i+2*length) sorted[z++]=list[y++];
    }
}