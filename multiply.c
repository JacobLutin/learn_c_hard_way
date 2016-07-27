#include <stdio.h>

unsigned int multiply(unsigned int x, unsigned int y);

int main(int argc, char *argv[])
{
	int a, b;

	scanf("%d %d", &a, &b);

	printf("%d\n", multiply(a, b));

	return 0;
}

unsigned int multiply(unsigned int x, unsigned int y)
{
	if (x == 1)
	{
		return y;
	}
	else if (x > 1)
	{
		return y + multiply(x-1, y);
	}

	return 0;
}