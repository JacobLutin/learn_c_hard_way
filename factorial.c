#include <stdio.h>

unsigned int factorial(unsigned int x);

int main(int argc, char *argv[])
{
	int a;

	printf("%lu\n", sizeof(unsigned int));

	if ((scanf("%d", &a) == 1) && a >= 0)
	{
		printf("factorial = %d\n", factorial(a));
	}
	else
	{
		printf("I/O error.\n");
	}

	return 0;

}

unsigned int factorial(unsigned int x)
{
	if (x == 0)
	{
		return 1;
	}
	else if (x > 0)
	{
		return x * factorial(x-1);
	}

	return 0;
}
