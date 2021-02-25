#include <stdio.h>

void Series_Sum( double sum[] );

int main()
{
    int i;
    double x, sum[3001];
	
    Series_Sum( sum );

    x = 0.0;
    for (i=0; i<3001; i++)
        printf("%6.2f %16.12f\n", x + (double)i * 0.10, sum[i]);

    return 0;
}

void Series_Sum(double sum[])
{
	int i,j;
	double result;
	for (i=0;i<=50;i++) 
	{
		result=0;
		for (j=1;j<10000; j++) {
		 	result+=1.0/(j*(j+i*0.10)*(j+1.0));
		} 
		sum[i]+=(1.0-i*0.10)*(result+1.0/200000000)+1.0;
	}
	for (i=1;i<11;i++) 
	{
		for(j=5;j<300;j++){
			sum[i+j*10] = ((i*0.10+j-1)*sum[i+(j-1)*10]+1.0/(i*0.10+j))/(i*0.10+j);
		}
	}
}