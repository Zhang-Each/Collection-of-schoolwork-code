#include <stdio.h>
#include <stdlib.h>
#define ERROR 1e8
typedef int ElementType;
typedef enum { push, pop, end } Operation;

typedef struct StackRecord *Stack;
struct StackRecord  {
    int Capacity;       /* maximum size of the stack array */
    int Top1;           /* top pointer for Stack 1 */
    int Top2;           /* top pointer for Stack 2 */
    ElementType *Array; /* space for the two stacks */
};

Stack CreateStack( int MaxElements );
int IsEmpty( Stack S, int Stacknum );
int IsFull( Stack S );
int Push( ElementType X, Stack S, int Stacknum );
ElementType Top_Pop( Stack S, int Stacknum );

Operation GetOp();  /* details omitted */
void PrintStack( Stack S, int Stacknum ); /* details omitted */

int main()
{
    int N, Sn, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while ( !done ) {
        switch( GetOp() ) {
        case push: 
            scanf("%d %d", &Sn, &X);
            if (!Push(X, S, Sn)) printf("Stack %d is Full!\n", Sn);
            break;
        case pop:
            scanf("%d", &Sn);
            X = Top_Pop(S, Sn);
            if ( X==ERROR ) printf("Stack %d is Empty!\n", Sn);
            break;
        case end:
            PrintStack(S, 1);
            PrintStack(S, 2);
            done = 1;
            break;
        }
    }
    return 0;
}
int real_top(int m,int n)
{
    if(m>n){
        return m;
    }
    else return n;
}
Stack CreateStack( int MaxElements )
{
    Stack X;
    X=malloc(sizeof(struct StackRecord));
    X->Array=malloc(sizeof(ElementType)*MaxElements);
    X->Capacity=MaxElements;
    X->Top1=-1;
    X->Top2=MaxElements;

    return X;
}

int IsFull( Stack S )
{
    int a,b,c;
    a=S->Top1;
    b=S->Top2;
    c=b-a;
    if(c==1){
        return 1;
    }
    else return 0;
}

int IsEmpty( Stack S, int Stacknum )
{
    if(Stacknum==1){
        if(S->Top1==-1){
            return 1;
        }
        else return 0;
    }
    else{
        if(S->Top2==S->Capacity){
            return 1;
        }
        else return 0;
    }
}

ElementType Top_Pop( Stack S, int Stacknum )
{
    int result;
    if(!IsEmpty(S,Stacknum)){
        if(Stacknum==1){
            result=S->Array[S->Top1];
            S->Top1--;
            return result;
        }
        else{
            result=S->Array[S->Top2];
            S->Top2++;
            return result;
        }
    }
    else{
        return ERROR;
    }
}

int Push( ElementType X, Stack S, int Stacknum )
{
    if(IsFull(S)){
        return 0;
    }
    else{
        if(Stacknum==1){
            S->Top1++;
            S->Array[S->Top1]=X;
        }
        else{
            S->Top2--;
            S->Array[S->Top2]=X;
        }
    }
    return 1;
}