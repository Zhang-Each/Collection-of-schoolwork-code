#include <stdio.h>

#define MAX_SIZE 10

int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN);

int main()
{
    int n, MAXN, m, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], v[MAX_SIZE];
    double lambda, TOL;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%lf", &a[i][j]);
    scanf("%lf %d", &TOL, &MAXN);
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        scanf("%lf", &lambda);
        for (j = 0; j < n; j++)
            scanf("%lf", &v[j]);
        switch (EigenV(n, a, &lambda, v, TOL, MAXN)) {
        case -1:
            printf("%12.8f is an eigenvalue.\n", lambda);
            break;
        case 0:
            printf("Maximum number of iterations exceeded.\n");
            break;
        case 1:
            printf("%12.8f\n", lambda);
            for (k = 0; k < n; k++)
                printf("%12.8f ", v[k]);
            printf("\n");
            break;
        }
    }

    return 0;
}

/* Your function will be put here */
#include <math.h>
void set(double a[][MAX_SIZE], double b[][MAX_SIZE], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b[i][j] = a[i][j];
        }
    }
}
int Factorization(int n, double a[][MAX_SIZE])
{
    int i,j,k;
    double w[MAX_SIZE];
    for (i=0;i<=n-2;i++) {
        if (a[i][i] == 0) {
            return 1;
        }
        for (j=i+1;j<n;j++) {
            a[j][i]=a[j][i]/a[i][i];
            for (k=i+1;k<n;k++) {
                a[j][k]-=a[j][i]*a[i][k];
            }
        }
    }
    if (a[n-1][n-1]==0)
        return 1;
    return 0;
}
int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN)
{
    int maxi,i,j;
    double max,u,b[MAX_SIZE][MAX_SIZE];
    set(a,b,n);
    for (int i=0;i<n;i++) a[i][i]-=*lambda;
    if(Factorization(n,a)==1){
        set(b,a,n);
        return -1;
    }
    max=0.0;
    for (i=0;i<n;i++){
        if (fabs(max) <= fabs(v[i]))
            max=v[i];
    }
    for (i=0;i<n;i++) v[i]/=max;;
    double w[MAX_SIZE];
    int count=1;
    while(count<=MAXN){
        for(i=0;i<n;i++) w[i]=v[i];
        double sum = 0,x[MAX_SIZE];
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
            for (j=i+1;j<n;j++) sum +=v[j]*a[i][j];
            if(a[i][i]==0){
                for(int l=0;l<n;l++){
                    for(int t=0;t<n;t++){
                        a[l][t]=b[l][t];
                    }
                }
                return -1;
            }
            v[i]=(x[i]-sum)/a[i][i];
        }
        max=0;
        for (i=0;i<n;i++) {
            if (fabs(max) <= fabs(v[i])) {
                max=v[i];
            }
        }
        for (i=0;i<n;i++)  v[i]/=max;
        double err = 0;
        for (i=0;i<n;i++) {
            if (fabs(err) < fabs(w[i]-v[i])) {
                err = fabs(w[i]-v[i]);
            }
        }
        if (err< TOL) {
            *lambda+=1/max;
            for(i=0;i<n;i++){
                for(j=0;j<n;j++){
                    a[i][j]=b[i][j];
                }
            }
            return 1;
        }
        count++;
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a[i][j]=b[i][j];
        }
    }
    return 0;
}