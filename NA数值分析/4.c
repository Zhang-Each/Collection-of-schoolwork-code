#include <stdio.h>
#include <math.h>

#define MAX_SIZE 10
#define bound pow(2, 127)
#define ZERO 1e-9 /* X is considered to be 0 if |X|<ZERO */

enum bool { false = 0, true = 1 };
#define bool enum bool

int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );

int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );

int main()
{
    int n, MAXN, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE], x[MAX_SIZE];
    double TOL;

    scanf("%d", &n);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++)
            scanf("%lf", &a[i][j]);
        scanf("%lf", &b[i]);
    }
    scanf("%lf %d", &TOL, &MAXN);

    printf("Result of Jacobi method:\n");
    for ( i=0; i<n; i++ )
        x[i] = 0.0;
    k = Jacobi( n, a, b, x, TOL, MAXN );
    switch ( k ) {
        case -2:
            printf("No convergence.\n");
            break;
        case -1: 
            printf("Matrix has a zero column.  No unique solution exists.\n");
            break;
        case 0:
            printf("Maximum number of iterations exceeded.\n");
            break;
        default:
            printf("no_iteration = %d\n", k);
            for ( j=0; j<n; j++ )
                printf("%.8f\n", x[j]);
            break;
    }
    printf("Result of Gauss-Seidel method:\n");
    for ( i=0; i<n; i++ )
        x[i] = 0.0;
    k = Gauss_Seidel( n, a, b, x, TOL, MAXN );
    switch ( k ) {
        case -2:
            printf("No convergence.\n");
            break;
        case -1: 
            printf("Matrix has a zero column.  No unique solution exists.\n");
            break;
        case 0:
            printf("Maximum number of iterations exceeded.\n");
            break;
        default:
            printf("no_iteration = %d\n", k);
            for ( j=0; j<n; j++ )
                printf("%.8f\n", x[j]);
            break;
    }

    return 0;
}

int Iszero(double x)
{
    if(fabs(x)<ZERO){
        return 1;
    }
    else return 0;
}

int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN )
{
    int i,j,row;
    double err,xi,max,t1,t2,t3;

    for(i=0;i<n;i++){
        max=fabs(a[i][i]);
        row=i;

        for(j=i+1;j<n;j++){
            if(fabs(a[j][i])>max){
                max=a[j][i];
                row=j;
            }
        }

        if(Iszero(max)){
            for(j=0;j<i;j++){
                if(fabs(a[j][i])>max){
                    max=a[j][i];;
                    row=j;
                }
            }
            if(Iszero(max)){
                return -1;
            }
        for(j=0;j<n;j++){
                a[i][j]+=a[row][j];
                b[i]+=b[row];
            }
        }

        else if(row!=i){
            for(j=0;j<n;j++){
                t1=a[row][j];
                a[row][j]=a[i][j];
                a[i][j]=t1;
            }
            t2=b[row];
            b[row]=b[i];
            b[i]=t2;
        }
    }

    for(i=0;i<n;i++) x[i]=0.0;

    int k=1;
    while(k<MAXN){
        err=0.0;
        double y[MAX_SIZE]={0.0};
        for(i=0;i<n;i++){
            xi=x[i];
            t3=0.0;
            for(j=0;j<n;j++){
                if(j!=i){
                    t3+=x[j]*a[i][j];
                }
            }
            y[i]=(b[i]-t3)/a[i][i];
            if(fabs(y[i])>bound){
                return -2;
            }
            if(err<fabs(xi-y[i])){
                err=fabs(xi-y[i]);
            }
        }
        for(i=0;i<n;i++){
            x[i]=y[i];
        }
        if(err<TOL) return k;
        k++;
    }
    
    return 0;
}

int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN )
{
    int i,j,k,row;
    double err,xi,max,t1,t2,t3;

    for(i=0;i<n;i++){
        max=fabs(a[i][i]);
        row=i;

        for(j=i+1;j<n;j++){
            if(fabs(a[j][i])>max){
                max=a[j][i];
                row=j;
            }
        }

        if(Iszero(max)){
            for(j=0;j<i;j++){
                if(fabs(a[j][i])>max){
                    max=a[j][i];;
                    row=j;
                }
            }
            if(Iszero(max)){
                return -1;
            }
        for(j=0;j<n;j++){
                a[i][j]+=a[row][j];
                b[i]+=b[row];
            }
        }

        else if(row!=i){
            for(j=0;j<n;j++){
                t1=a[row][j];
                a[row][j]=a[i][j];
                a[i][j]=t1;
            }
            t2=b[row];
            b[row]=b[i];
            b[i]=t2;
        }
    }

    for(i=0;i<n;i++) x[i]=0.0;
    k=1;
    while(k<MAXN){
        err=0.0;
        for(i=0;i<n;i++){
            xi=x[i];
            t3=0.0;
            for(j=0;j<n;j++){
                t3+=x[j]*a[i][j];
            }
            x[i]=x[i]+(b[i]-t3)/a[i][i];
            if(fabs(x[i])>bound){
                return -2;
            }
            if(err<fabs(xi-x[i])){
                err=fabs(xi-x[i]);
            }
        }
        if(err<TOL) return k;
        k++;
    }

    return 0;
}