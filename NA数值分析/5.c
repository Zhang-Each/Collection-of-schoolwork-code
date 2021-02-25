#include <stdio.h>

#define MAX_SIZE 10

int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN);

int main()
{
    int n, MAXN, m, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], v[MAX_SIZE];
    double lambda, TOL;

    scanf("%d", &n);
    for (i=0; i<n; i++) 
        for (j=0; j<n; j++) 
            scanf("%lf", &a[i][j]);
    scanf("%lf %d", &TOL, &MAXN);
    scanf("%d", &m);
    for (i=0; i<m; i++) {
        scanf("%lf", &lambda);
        for (j=0; j<n; j++)
            scanf("%lf", &v[j]);
        switch (EigenV(n, a, &lambda, v, TOL, MAXN)) {
            case -1: 
                printf("%12.8f is an eigenvalue.\n", lambda );
                break;
            case 0:
                printf("indexmum number of iterations exceeded.\n");
                break;
            case 1:
                printf("%12.8f\n", lambda );
                for (k=0; k<n; k++)
                    printf("%12.8f ", v[k]);
                printf("\n");
                break;
        }
    }

    return 0;
}

#include <math.h>
#include <stdlib.h>
#include <string.h>
double b[MAX_SIZE][MAX_SIZE];
int Factorization(int n, double a[][MAX_SIZE])
{
    int i,j;
    double buffer[MAX_SIZE];
    for (i=0;i<=n-2;i++) {
        if (a[i][i] == 0) {
            return 1;
        }
        for (j = i + 1; j < n; j++) {
            a[j][i] = a[j][i] / a[i][i];
            for (int k = i + 1; k < n; k++) {
                a[j][k] -= a[j][i] * a[i][k];
            }
        }
    }
    if (a[n - 1][n - 1] == 0) {
        return 1;
    }
    return 0;
}


int Solve(int n, double a[][MAX_SIZE], double v[])
{
    int i,j;
    double sum = 0;
    double x[MAX_SIZE];
    x[0]=v[0];
    for (i=1;i<=n-1;i++) {
        sum = 0;
        for (j=0;j<i;j++) {
            sum += x[j] * a[i][j];
        }
        x[i] = v[i] - sum;
    }
    v[n-1] = x[n-1]/a[n-1][n-1];
    for (i=n-2;i>=0;i--) {
        sum = 0;
        for (j=i+1;j<n;j++) {
            sum +=v[j]*a[i][j];
        }
        if(a[i][i]==0){
            return 1;
        }
        v[i]=(x[i]-sum)/a[i][i];
    }
    return 0;
}

int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN)
{
    memcpy(b, a, sizeof(double) * MAX_SIZE * MAX_SIZE);
    int index,i,j;
    double max,result;
    double u[MAX_SIZE];
    for (int i = 0; i < n; i++) {
        a[i][i] -= *lambda;
    }
    if(Factorization(n,a)==1){
        memcpy(a, b, sizeof(double)*MAX_SIZE*MAX_SIZE);
        return -1;
    }
    index=n-1;
    for (i=n-2;i>= 0;i--) {
        if (fabs(v[index])<=fabs(v[i])) {
            index = i;
            max=fabs(v[i]);
        }
    }
    for (i=0;i<n;i++) {
        v[i]/=max;
    }

    double buffer[MAX_SIZE];
    int count=1;
    while(count<=MAXN){
        memcpy(buffer, v, sizeof(double) * n);
        if (Solve(n, a, v)==1) {
            memcpy(a, b, sizeof(double) * MAX_SIZE * MAX_SIZE);
            return -1;
        }
        index=0;
        max=0.0;
        for (i=0;i<n;i++) {
            if (fabs(v[index]) <= fabs(v[i])) {
                index=i;
                max=v[i];
            }
        }
        result=v[index];
        for (i=0;i<n;i++)  v[i]/=max;
        double err=0.0;
        for (i=0;i<n;i++) {
            if (fabs(err)<fabs(u[i]-v[i])) {
                err=fabs(u[i]-v[i]);
            }
        }
        if (err<TOL){
            *lambda+=1/result;
            for(i=0;i<n;i++){
                for(j=0;j<n;j++){
                    a[i][j]=b[i][j];
                }
            }
            return 1;
        }
        count++;
    }
    return 0;
}