#include <stdio.h>
#include <math.h>

double f0( double x, double l, double t )
{
    return sqrt(1.0+l*l*t*t*cos(t*x)*cos(t*x));
}

double Integral(double a, double b, double (*f)(double x, double y, double z), 
double eps, double l, double t);

int main()
{
    double a=0.0, b, eps=0.005, l, t;

    scanf("%lf %lf %lf", &l, &b, &t);
    printf("%.2f\n", Integral(a, b, f0, eps, l, t));

    return 0;
}

double Integral(double a, double b, double (*f)(double x, double y, double z), double eps, double l, double t)
{
    int i,j;
    double sum,h,R[3][100];
    h=b-a;
    R[1][1]=(f(a,l,t)+f(b,l,t))*h/2;
    for(i=2;i<100;i++)
    {
        sum=0;
        int k=pow(2,i-2);
        for(j=1;j<=k;++j)
        {
            sum=sum+f(a+(j-0.5)*h,l,t);
        }
        R[2][1]=0.5*(R[1][1]+h*sum);
        for(j=2;j<=i;j++)
        {
            R[2][j]=R[2][j-1]+(R[2][j-1]-R[1][j-1])/(pow(4,j-1)*1.0-1.0);
        }
        double error;
        error=R[2][i]-R[1][i-1];
        if(fabs(error)<eps&&h<1)
            break;
        h=h/2;
        for(j=1;j<=i;j++)
            R[1][j]=R[2][j];
    }
    return R[2][i]/100;
}