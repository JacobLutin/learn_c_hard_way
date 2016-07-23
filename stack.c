#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA 100

struct Stack
{
	int data[MAX_DATA];
	int count;
};

void Stack_debug(struct Stack *stack)
{
	printf("%p\n", sizeof(stack));
	printf("%p\n", sizeof(stack->data));
	printf("%p\n", stack->data);
	printf("%d\n", stack->count);
}

struct Stack *Stack_init(void)
{
	struct Stack *stack = malloc(sizeof(struct Stack));

	stack->count = 0;

	return stack;
}

int Stack_push(struct Stack *stack, int num)
{
	int count = stack->count;

	if (count == MAX_DATA-1)
	{
		printf("Push error.");
		return 1;
	}
		
	
	stack->data[count] = num;
	stack->count++;

	return 0;

}

int Stack_pop(struct Stack *stack, int *num)
{
	int count = stack->count;

	if (count == 0)
	{
		printf("pop error.");
		return 1;
	}

	*num = stack->data[count-1];
	stack->count--;

	return 0;
}

int main()
{	
	struct Stack *stack = Stack_init();
	long int memory;

	Stack_push(stack, 1);
	Stack_push(stack, 2);
	Stack_push(stack, 3);

	Stack_debug(stack);

	int num;

	Stack_pop(stack, &num);
	printf("Number = %d\n", num);

	Stack_pop(stack, &num);
	printf("Number = %d\n", num);

	Stack_pop(stack, &num);
	printf("Number = %d\n", num);

	Stack_debug(stack);

	memory = &stack;
	printf("%ld\n", memory);	
	memory = malloc(sizeof(stack));
	printf("%ld\n", memory);
	memory = malloc(sizeof(stack));
	printf("%ld\n", memory);
	memory = stack;
	printf("%ld\n", memory);
	memory = &stack;
	printf("%ld\n", memory);
}
