#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include <assert.h>

int Object_init(void *self)
{
	return 1;
}

void Object_describe(void *self)
{
	Object *object = self;
	printf("%s\n", object->description);
}

void Object_destroy(void *self)
{
	Object *object = self;

	if (object != NULL)
	{
		if (object->description != NULL)
			free(object->description);

		free(object);
	}
}

void *Object_move(void *self, Direction direction)
{
	printf("You can't move there.\n");
	return NULL;
}

int Object_attack(void *self, int damage)
{
	printf("You can't attack that.\n");
	return 0;
}

void *Object_new(size_t size, Object proto, char *description)
{
	if (!proto.init) proto.init = Object_init;
	if (!proto.describe) proto.describe = Object_describe;
	if (!proto.destroy) proto.destroy = Object_destroy;
	if (!proto.move) proto.move = Object_move;
	if (!proto.attack) proto.attack = Object_attack;

	Object *el = calloc(1, size);
	*el = proto;

	el->description = strdup(description);

	if (el->init(el) != 1)
	{
		el->destroy(el);
		return NULL;
	}

	return el;

}









