#include<stdio.h>
#include <math.h>
#pragma warning(disable : 4996)

int main()
{
	int cheak = 0;
	float pai;
	pai = 3.1415926;
	float ft=0;
	int A, B, C;
	float t = 0;
	scanf("%d", &A);
	scanf("%d", &B);
	scanf("%d", &C);
	
	do{
		
		t++;
		ft = A*(t / 1) + B*sin(C*(t / 1)*pai);
		printf("%f waitingÅEÅEÅE\n",ft);
		

	} while (ft<99.9 || ft>100.1);
	
	printf("%f\n", t/1);
	printf("%f\n", ft);

}

