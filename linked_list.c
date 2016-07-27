#include <stdio.h>
#include <stdlib.h>

/**************************************************************************
	Node declaration
**************************************************************************/

typedef struct Node
{
	int val;
	struct Node *next;
} Node_t;

/**************************************************************************
	print_list function
**************************************************************************/

int print_list(Node_t *head)
{
	Node_t *current = head;

	while (current != NULL)
	{
		printf("%d ", current->val);
		current = current->next;
	}

	printf("\n");

	return 0;
}

/**************************************************************************
	Node_init function
**************************************************************************/

Node_t *Node_init(int num)
{
	Node_t *head = malloc(sizeof(Node_t));

	head->val = num;
	head->next = NULL;

	return head;
}

/**************************************************************************
	Node_push function
**************************************************************************/

void Node_push(Node_t **head, int num)
{
	Node_t *new_node = malloc(sizeof(Node_t));

	new_node->val = num;
	new_node->next = *head;

	*head = new_node;
}

/**************************************************************************
	Node_pop function
**************************************************************************/

int Node_pop(Node_t **head, int *num)
{
	Node_t *next_node;

	if (*head == NULL)
	{
		return 0;
	}

	*num = (*head)->val;
	next_node = (*head)->next;

	free(*head);

	*head = next_node;

	return 1;
}

/**************************************************************************
	Node_remove_last function
**************************************************************************/

int Node_remove_last(Node_t **head, int *num)
{
	if (*head == NULL)
	{
		return 0;
	}

	Node_t *prev;
	Node_t *current = *head;
	*num = (current)->val;

	if (current->next == NULL)
	{
		free(*head);
		*head = NULL;

		return 1;
	}

	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
		*num = current->val;
	}

	free(prev->next);
	prev->next = NULL;
		
	return 1;
}


int main(int argc, char *argv[])
{
	int num;
	Node_t *head = Node_init(1);

	Node_push(&head, 5);
	Node_push(&head, 10);
	Node_push(&head, 0);
	print_list(head);

	if (Node_remove_last(&head, &num))
		printf("Removed element: %d\n", num);

	if (Node_remove_last(&head, &num))
		printf("Removed element: %d\n", num);

	if (Node_remove_last(&head, &num))
		printf("Removed element: %d\n", num);

	if (Node_remove_last(&head, &num))
		printf("Removed element: %d\n", num);

	print_list(head);

	Node_push(&head, 56);
	Node_push(&head, 88);

	if (Node_remove_last(&head, &num))
		printf("Removed element: %d\n", num);

	if (Node_remove_last(&head, &num))
		printf("Removed element: %d\n", num);

	if (Node_remove_last(&head, &num))
		printf("Removed element: %d\n", num);

	print_list(head);

	return 0;
}







