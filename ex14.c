#include <stdio.h>
#include <ctype.h>

int can_print_it(char ch);
void print_letters(char arg[]);

void print_arguments(int argc, char *argv[])
{
	int i;
	for (i = 0; i < argc; i++)
	{
		print_letters(argv[i]);
		printf("\n");

	}
}

void print_letters(char arg[])
{
	int i;
	for (i = 0; arg[i] != '\0'; i++)
	{
		char ch = arg[i];

		if (can_print_it(ch) == 1)
		{
			printf("%d: '%c'; ", ch, ch);
		}
	}
}

int can_print_it(char ch)
{
	return isalpha(ch) || isblank(ch);
}

int main(int argc, char *argv[])
{
	print_arguments(argc, argv);
	return 0;
}

