#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
	char *name;
	int age;
	int height;
	int weight;
	//int phone;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
	printf("Location = %p\n", malloc(sizeof(struct Person)));
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);

	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;
	//who->phone = phone;

	return who;
}

void Person_destroy(struct Person *who)
{
	assert(who != NULL);

	free(who->name);
	free(who);
}

void Person_print(struct Person *who)
{
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
	//printf("\tPhone: %d\n", who->phone);
}

int main(int argc, char *argv[])
{
	// make two people structures
	struct Person *joe = Person_create("Joe Alex", 32, 176, 65);

	struct Person *frank = Person_create("Frank Blanc", 26, 163, 86);

	printf("Joe is at memory location %p:\n", joe);
	Person_print(joe);

	printf("Frank is at memory location %p:\n", frank);
	Person_print(frank);

	joe->age += 20;
	joe->height += 10;
	Person_print(joe);

	frank->age -= 20;
	frank->weight += 25;
	Person_print(frank);

	Person_destroy(joe);
	Person_destroy(frank);

	return 0;
}
