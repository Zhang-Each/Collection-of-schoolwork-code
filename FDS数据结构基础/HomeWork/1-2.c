#include <stdio.h>
#include <stdlib.h>
typedef struct Node *PtrToNode;
struct Node  {
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

Polynomial Read(); /* details omitted */
void Print( Polynomial p ); /* details omitted */
Polynomial Add( Polynomial a, Polynomial b );

int main()
{
    Polynomial a, b, s;
    a = Read();
    b = Read();
    s = Add(a, b);
    Print(s);
    return 0;
}

int IsEmpty(Polynomial x)
{
    return x==NULL;
}

Polynomial Add( Polynomial a, Polynomial b )
{
    int x=IsEmpty(a);
    int y=IsEmpty(b);
    Polynomial c,d,p; //c is the answer list
    if(a!=1&&b==1){
        return a;
    }
    if(b!=1&&a==1){
        return b;
    }
    b=b->Next;
    a=a->Next;

    d=(Polynomial)malloc(sizeof(Polynomial));
    c=d;

    while(a!=NULL&&b!=NULL){
        p=(Polynomial)malloc(sizeof(Polynomial));
        d->Next=p;

        if(a->Exponent>b->Exponent){
            p->Coefficient=a->Coefficient;
            p->Exponent=a->Exponent;
            a=a->Next;
        }

        else if(b->Exponent>a->Exponent){
            p->Coefficient=b->Coefficient;
            p->Exponent=b->Exponent;
            b=b->Next;
        }
        else{
            if(a->Coefficient+b->Coefficient){
                a=a->Next;
                b=b->Next;
                continue;
            }
            else{
                p->Exponent=b->Exponent;
                p->Coefficient=a->Coefficient+b->Coefficient;
                a=a->Next;
                b=b->Next;
            }
        }

        d=p;
        p=p->Next;
    }

    if(a!=NULL){
        d->Next=a;
    }
    if(b!=NULL){
        d->Next=b;
    }

    return c;
}