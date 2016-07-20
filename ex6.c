#include <stdio.h>

int main(int argc, char *argv[])
{
	int distance = 100;
	float power = 2.345f;
	double super_power = 5678.4532;
	char initial = 'A';
	char first_name[] = "Jacob";
	char last_name[] = "Lutin";

	printf("You are %d miles away.\n", distance);
	printf("You are %f levels of power.\n", power);
	printf("You have %f awesome super power.\n", super_power);
	printf("I have an initial %c.\n", initial);
	printf("My name is %s %s.\n", first_name, last_name);

	return 0;
}
