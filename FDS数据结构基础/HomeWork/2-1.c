#include <stdio.h>
#include <stdlib.h>

typedef double ElementType;
#define Infinity 1e8
#define Max_Expr 30   /* max size of expression */

ElementType EvalPostfix( char *expr );

int main()
{
    ElementType v;
    char expr[Max_Expr];
    gets(expr);
    v = EvalPostfix( expr );
    if ( v < Infinity )
        printf("%f\n", v);
    else
        printf("ERROR\n");
    return 0;
}

void reset(char x[],int y)
{
    int i;
    for(i=0;i<y;i++){
        x[i]=0;
    }
}

int isnumber(char x)
{
    if(x>='0'&&x<='9'){
        return 1;
    }
    return 0;
}

int isfloatpoint(char x)
{
    if(x=='.') return 1;
    else return 0;
}

ElementType EvalPostfix( char *expr ){
    double stack[31];//a stack to memory the numbers
    char word[10];
    int i,j,k;

    i=0;
    k=0;

    while (expr[i]!='\0') {
        j=0;
        while (expr[i]==' ') 
            i=i+1;
        while(isnumber(expr[i])||isfloatpoint(expr[i])||(expr[i]=='-'&&expr[i+1]!=' '&&expr[i+1]!='\0')){
            word[j]=expr[i];
            j=j+1;
            i=i+1; //memory a number before the operations
        }

        if(expr[i]==' '||(k==0&&expr[i+1]=='\0')) {
            stack[k]=atof(word);
            reset(word,j); //make the array word all 0s
            k=k+1;
            i=i+1;
        }
        else if(expr[i]!=' '&&(!(isnumber(expr[i])))&&(expr[i+1]==' '||expr[i+1]=='\0')){
            if(expr[i]=='+'){
                stack[k-2]=stack[k-1]+stack[k-2];
                //stack[k-1]=0;
            }
            else if(expr[i]=='-'){
                stack[k-2]=stack[k-2]-stack[k-1];
                //stack[k-1]=0;
            }
            else if(expr[i]=='*'){
                stack[k-2]=stack[k-2]*stack[k-1];
                //stack[k-1]=0;
            }
            else if(expr[i]=='/'){
                if(stack[k-1]==0){
                    return 1e9;
                }
                else{
                    stack[k-2]=stack[k-2]/stack[k-1];
                    //stack[k-1]=0;
                }
            } //operations
            else{
                break;
            }
            k=k-1;
            i=i+1;
        }
    }
    if (!k) return Infinity;
    //if(stack[k-1]==0) return Infinity;
    return stack[k-1];
}