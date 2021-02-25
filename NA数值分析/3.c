#include <stdio.h>

#define Max_size 10000 /* max number of dishes */

void Price( int n, double p[] );

int main()
{
    int n, i;
    double p[Max_size];

    scanf("%d", &n);
    for (i=0; i<n; i++) 
        scanf("%lf", &p[i]);
    Price(n, p);
    for (i=0; i<n; i++)
        printf("%.2f ", p[i]);
    printf("\n");

    return 0;
}

struct number{
	double r;
	double k;
};

void Price( int n, double p[] )
{
	int i;
	double l[10001],u[10001];
	struct number b[10001],z[10001],x[10001];
    for(i=1;i<=n-1;i++){
        b[i].r= p[i-1];
        if(i==1||i==n-1){
            b[i].k=-0.5;
        }
        else{
            b[i].k=0;
        }
        //printf("%.2f %.2f\n",b[i].r,b[i].k);
    }
    l[1]=2;
    u[1]=0.25;
    for(i=2;i<n;i++){
        l[i]=2-0.5*u[i-1];
        u[i]=0.5/l[i];
    }

    z[1].k=0.5*b[1].k;
    z[1].r=0.5*b[1].r;
    for(i=2;i<=n-1;i++){
        z[i].r=(b[i].r-0.5*z[i-1].r)/l[i];
        z[i].k=(b[i].k-0.5*z[i-1].k)/l[i];
    }
    x[n-1]=z[n-1];
    for(i=n-2;i>=1;i--){
        x[i].r=z[i].r-u[i]*x[i+1].r;
        x[i].k=z[i].k-u[i]*x[i+1].k;
    }

    double m;
    m=p[n-1]-0.5*(x[n-1].r+x[1].r);
    m=m/(2+0.5*(x[n-1].k+x[1].k));
    p[n-1]=m;
    for(i=0;i<n-1;i++){
        p[i]=x[i+1].r+m*x[i+1].k;
    }
}