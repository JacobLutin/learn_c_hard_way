#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(char *message)
{
	if (errno)
	{
		perror(message);
	}
	else
	{
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

// typedef creates a fake type, in this case for a function pointer
typedef int (*compare_cb) (int a, int b);

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void array_print(int *array, int count)
{
	int i;
	for (i = 0; i < count; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");
}

// classic bubble sort that use compare_cb function to compare nums
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int i, j;
	int temp;

	int *target = malloc(count * sizeof(int));

	if (target == NULL)
	{
		die("Memory fail.");
	}

	memcpy(target, numbers, count * sizeof(int));

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < count - 1; j++)
		{
			if (cmp(target[j], target[j+1]) > 0)
			{
				swap(&target[j], &target[j+1]);
			}
		}
	}

	return target;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		die("USAGE: ./main 1 2 3 4 5");
	}

	int count = argc - 1;
	int i = 0;
	char **inputs = argv + 1;
	

	int *numbers = malloc(count * sizeof(int));

	if (numbers == NULL)
	{
		die("Memory fail.");
	}

	for (i = 0; i < count; i++)
	{
		numbers[i] = atoi(inputs[i]);
	}

	int *sorted = bubble_sort(numbers, count, sorted_order);
	array_print(sorted, count);

	free(numbers);
	free(sorted);

	return 0;
}

















