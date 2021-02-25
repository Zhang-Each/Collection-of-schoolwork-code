#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

List Reverse( List L )
{
    List y,z;
    int a[100],b[100];
    int len=0,i;
    y=L->Next;
    while(y!=NULL){
        a[len]=y->Element;
        y=y->Next;
        len++;
    }
    for(i=0;i<len;i++){
        b[i]=a[len-1-i];
    }
    z=L->Next;
    i=0;
    while(i<len){
        z->Element=b[i];
        i++;
        z=z->Next;
    }
    return L;
}