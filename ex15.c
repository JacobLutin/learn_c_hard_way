#include <stdio.h>

int main(int argc, char *argv[])
{
	int ages[] = {23, 15, 56, 45, 8};
	char *names[] = {"Jon", "Sansa", "Ramsey", "Eddard", "Tirion", "Arya"};

	int count = sizeof(ages) / sizeof(int);

	int i;
	for (i = 0; i < count; i++)
	{
		printf("%s has %d years alive\n", names[i], ages[i]);
	}

	printf("---\n");

	int *cur_ages = ages;
	char **cur_names = names;

	for (i = 0; i < count; i++)
	{
		printf("%s is %d years old\n", *(cur_names+i), *(cur_ages+i));
	}

	printf("---\n");

	return 0;
}
