#include <stdio.h>
#include <math.h>

#define ZERO 1e-13 /* X is considered to be 0 if |X|<ZERO */
#define MAXN 11    /* Max Polynomial Degree + 1 */

double Polynomial_finalroot(int n, double c[], double a, double b, double EPS);

int main()
{
    int n;
    double c[MAXN], a, b;
    double EPS = 0.00005;
    int i;

    scanf("%d", &n);
    for (i=n; i>=0; i--) 
        scanf("%lf", &c[i]);
    scanf("%lf %lf", &a, &b);
    printf("%.4f\n", Polynomial_finalroot(n, c, a, b, EPS));

    return 0;
}

double fx(int n, double c[], double x)
{
    int i;
    double result=0;
    for(i=n;i>= 0;i--)
        result=result*x+c[i];
    return result;
}

double dx(int n,double c[],double x)
{
    int i;
    double result=0;
    for(i=n;i>= 1;i--)
        result=result*x +i*c[i];
    return result;
}

double d2x(int n,double c[],double x)
{
    int i;
    double result = 0;
    for(i=n;i>=2;i--)
        result=result*x+i*(i-1)*c[i];
    return result;
}

int Newton(int n,double c[],double a,double b,double p0,double *p,double *error,double EPS)
{
	int i,convergence=0;
    for(i=0;i<1000;i++)
    {
        double f0,f1,f2,f;//f(p0),f'(p0),f''(p0)
        f0=fx(n,c,p0);
		if (fabs(f0)<ZERO){
			convergence=1;
			break;
        }

        f1=dx(n,c,p0);
        f2=d2x(n,c,p0);
        f=f1*f1-f0*f2;
		if (fabs(f)<ZERO){
			convergence=0;
			break;
		}
        *p=p0-f0*f1/f;
		if (*p>b||*p<a)
		{
			convergence=0;
			break;
		}
		if (fabs(*p-(p0))<EPS)
		{
			convergence=1;
			break;
		}
        p0=*p;
    }
	*error=fabs(fx(n,c,*p));
	return convergence;
}

double Polynomial_finalroot(int n, double c[], double a, double b, double EPS)
{
    int i,count=100;
    double p,min,finalroot;
    if(b<a){
        double t; 
        t=a;a=b;b=t;
    }

    double begin=(b-a)/count;
	min=999;
    for(i=0;i<=count;i++)
    {
        double p0=a+begin*i;
        double error;
		if (Newton(n,c,a,b,p0,&p,&error,EPS)==1&&error<min)
		{
			min=error;
			finalroot=p;
		}
    }
	return finalroot;
}