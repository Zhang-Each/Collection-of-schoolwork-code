#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define ElementType int
#define ERROR 1e5
typedef enum { push, pop, inject, eject, end } Operation;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next, Last;
};
typedef struct DequeRecord *Deque;
struct DequeRecord {
    PtrToNode Front, Rear;
};

Deque CreateDeque();
int Push( ElementType X, Deque D );
ElementType Pop( Deque D );
int Inject( ElementType X, Deque D );
ElementType Eject( Deque D );

Operation GetOp();          /* details omitted */
void PrintDeque( Deque D ); /* details omitted */

int main()
{
    ElementType X;
    Deque D;
    int done = 0;

    D = CreateDeque();
    while (!done) {
        switch(GetOp()) {
        case push: 
            scanf("%d", &X);
            if (!Push(X, D)) printf("Memory is Full!\n");
            break;
        case pop:
            X = Pop(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case inject: 
            scanf("%d", &X);
            if (!Inject(X, D)) printf("Memory is Full!\n");
            break;
        case eject:
            X = Eject(D);
            if ( X==ERROR ) printf("Deque is Empty!\n");
            break;
        case end:
            PrintDeque(D);
            done = 1;
            break;
        }
    }
    return 0;
}

void PrintDeque( Deque D )
{
    if(D -> Rear == D -> Front)
    {
        printf("Deque is Empty!");
        return;
    }
    printf("Inside Deque:");
    PtrToNode p = D -> Front -> Next;
    while(p)
    {
        printf(" %d",p -> Element);
        p = p -> Next;
    }
}

Operation GetOp()
{
    char s[10];
    scanf("%s",s);
    if(!strcmp(s,"Pop"))return pop;
    else if(!strcmp(s,"Push"))return push;
    else if(!strcmp(s,"Inject"))return inject;
    else if(!strcmp(s,"Eject"))return eject;
    else return end;
}

Deque CreateDeque()
{
    Deque X;
    X=(Deque)malloc(sizeof(struct DequeRecord));
    X->Front=(PtrToNode)malloc(sizeof(struct Node));
    X->Front->Last=NULL;
    X->Rear=X->Front;
    X->Rear->Next=NULL;
    return X;
}

int IsEmpty( Deque D)
{
    if(D->Front==D->Rear){
        return 1;
    }
    else return 0;
}

int Push( ElementType X, Deque D )
{
    PtrToNode m;
    m=(PtrToNode)malloc(sizeof(struct Node));
    if(!m){
        return 0;
    }
    else{
        m->Element=X;
        m->Next=D->Front->Next;
        if(m->Next!=NULL){
            m->Next->Last=m;
        }
        m->Last=D->Front;
        D->Front->Next=m;

        if(IsEmpty(D)==1) D->Rear=m;
        return 1;
    }
}

ElementType Pop( Deque D )
{
    if(IsEmpty(D)==1){
        return ERROR;
    }
    PtrToNode m;
    m=D->Front->Next;

    ElementType y;
    y=m->Element;

    if(D->Front->Next==D->Rear){
        D->Rear=D->Front;
        D->Rear->Next=NULL;
    }
    else{
    m->Next->Last=D->Front;
    D->Front->Next=m->Next;
    }
    free(m);
    return y;
}

int Inject( ElementType X, Deque D )
{
    PtrToNode m;
    m=(PtrToNode)malloc(sizeof(struct Node));
    if(!m){
        return 0;
    }

    if(IsEmpty(D)==1){
        D->Front->Next=m;
        m->Last=D->Front;
        D->Rear=m;
        return 1;
    }

    m->Element=X;
    m->Last=D->Rear;
    D->Rear->Next=m;
    m->Next=NULL;
    D->Rear=m;
    return 1;
}

ElementType Eject( Deque D )
{
    PtrToNode m;
    m=D->Rear;
    if(m==D->Front){
        return ERROR; 
    }
    ElementType y;
    y=m->Element;
    D->Rear=m->Last;
    m->Last->Next=NULL;
    free(m);

    return y;
}