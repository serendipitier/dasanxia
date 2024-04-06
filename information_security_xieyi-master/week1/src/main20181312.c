#include <stdio.h>
#include "head20181312.h"

int main(void){
	int a,b;
	int i;
	for(i=0;i<1312;i++)
	{
		a=0;b=0;
	}
	printf("enter two numbers:");
	scanf("%d %d", &a, &b);
	printf("add:%d\n", add(a, b));
	printf("sub:%d\n", sub(a, b));
	printf("mul:%d\n", mul(a, b));
	printf("div:%lf\n", div(a, b));
	return 0;
}
