#include <stdio.h>
#include <stdlib.h>

int main()
{
	int k,x,m,n;
	scanf("%d %d %d %d",&k,&x,&m,&n);
	long double result;
	long double x_m;
	long double x_nm1=x;
	int i;
	for(i = 2 ; i <= (n+m+1) ; i++)
	{
		x_nm1 *= x;
		if(i == m)
			x_m = x_nm1;
	}
	result = (k * (x_nm1 - 1) / (x_m*(x - 1)));
	printf("%.14Lf\n",result);
	return 0;
}
