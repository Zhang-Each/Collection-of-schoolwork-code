#include <stdio.h>
#include <math.h>
#define MAX_m 200
#define MAX_n 5

double f1(double x)
{
    return sin(x);
}

double f2(double x)
{
    return pow(x, 5);
}

int OPA(double (*f)(double t), int m, double x[], double w[],
        double c[], double *eps);

void print_results(int n, double c[], double eps)
{
    int i;
    printf("%d\n", n);
    for (i = 0; i <= n; i++)
        printf("%8.4e ", c[i]);
    printf("\n");
    printf("error = %6.2e\n", eps);
    printf("\n");
}

int main()
{
    int m, i, n;
    double x[MAX_m], w[MAX_m], c[MAX_n + 1], eps;
    m = 90;
    for (i = 0; i < m; i++)
    {
        x[i] = 3.1415926535897932 * (double)(i + 1) / 180.0;
        w[i] = 1.0;
    }
    eps = 0.001;
    n = OPA(f1, m, x, w, c, &eps);
    print_results(n, c, eps);
    m = 200;
    for (i = 0; i < m; i++)
    {
        x[i] = 0.01 * (double)i;
        w[i] = 1.0;
    }
    eps = 0.001;
    n = OPA(f2, m, x, w, c, &eps);
    print_results(n, c, eps);
    getchar();
    return 0;
}

/* Your function will be put here */
double error(double (*f)(double t), int m, int k, double x[], double w[], double c[])   
{   
    double result = 0.0;   
    for(int i = 0; i < m; i++)   
    {   
        double p = 0;   
        for(int j = 0; j <= k; j++) 
            p += c[j] * pow(x[i], j);   
        result += w[i] * (f(x[i]) - p)*(f(x[i]) - p);   
    }   
    return result;   
}   
void set(double  *a,double *b)
{
    *a=0;
    *b=0;
}
void cal(int m,double b[],double x[],double w[],double k,double *p,double *q)
{
    for(int i = 0; i < m; i++)   
    {   
        double f = 0, g = 0;   
        for(int j = 0; j <= k; j++)   
        {    
            f += b[j] * pow(x[i], j) * x[i];   
            g += b[j] * pow(x[i], j);   
        }   
        *p += w[i] * f * g;   
        *q += w[i] * g * g;   
    } 
}
int OPA(double (*f)(double t), int m, double x[], double w[], double c[], double *eps)   
{   
    double b[MAX_m]={0}, b1[MAX_m]={0}, b2[MAX_m]={0},B[MAX_m]={0}, C[MAX_m]={0}, p,q;    
    for(int i = 0; i <= MAX_n; i++)  c[i] = 0;   
    int k = 0;   
    b2[k] = 1;   
    set(&p,&q); 
    for(int i = 0; i < m; i++){   
        double fv = 0, gv = 0;   
        for(int j = 0; j <= k; j++)   
            fv += b2[j] * pow(x[i], j);   
        gv = f(x[i]);   
        p += w[i] * fv * gv;   
        q += w[i] * fv * fv;   
    }   
    double a = p / q;   
    for(int i = 0; i <= k; i++)   
        c[i] += a * b2[i];   
    set(&p,&q);  
    cal(m,b2,x,w,k,&p,&q);
    B[k] = p / q;   
    k = 1;   
    b1[0] = -B[0];   
    b1[1] = 1;   
    set(&p,&q);   
    for(int i = 0; i < m; i++){   
        double fv = 0, gv = 0;   
        for(int j = 0; j <= k; j++)   
            fv += b1[j] * pow(x[i], j);   
        gv = f(x[i]);   
        p += w[i] * fv * gv;   
        q += w[i] * fv * fv;   
    }   
    a = p / q;   
    for(int i = 0; i <= k; i++)   
        c[i] += a * b1[i];   
    double err;
    while(k < MAX_n)   
    {   
        err = error(f, m, k, x, w, c);   
        if(err < *eps){   
            *eps = err;   
            return k;   
        }   
        set(&p,&q); 
        cal(m,b1,x,w,++k,&p,&q); 
        B[k] = p / q;   
        set(&p,&q);  
        for(int i = 0; i < m; i++){   
            double fv = 0, gv = 0, r;   
            for(int j = 0; j <= k; j++)   
                fv += b1[j] * pow(x[i], j) * x[i];    
            for(int j = 0; j <= k; j++)    
                gv += b2[j] * pow(x[i], j);
            p += w[i] * fv * gv;   
            q += w[i] * gv * gv;   
        }   
        C[k] = p / q;   
        b[0] = -B[k] * b1[0] - C[k] * b2[0];   
        for(int i = 1; i <= k; i++)   
            b[i] =  b1[i-1] - B[k] * b1[i] - C[k] * b2[i];    
        set(&p,&q); 
        for(int i = 0; i < m; i++){   
            double fv=0,gv=0;  
            for(int j = 0; j <= k; j++)   
                fv += b[j] * pow(x[i], j);   
            gv = f(x[i]);   
            p += w[i] * fv * gv;   
            q += w[i] * fv * fv;   
        }   
        a = p / q;   
        for(int i = 0; i <= k; i++)   
            c[i] += a * b[i];   
        for(int i = 0; i <= k; i++){   
            b2[i] = b1[i];   
            b1[i] = b[i];   
        }   
    }   
    *eps = error(f, m, k, x, w, c);   
    return k;   
}