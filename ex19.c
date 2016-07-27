#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "ex19.h"


/**************************************************************************
	Monster functions
**************************************************************************/

int Monster_attack(void *self, int damage)
{
	Monster *monster = self;

	printf("You attack %s!\n", monster->_(description));

	monster->hit_points -= damage;

	if (monster->hit_points > 0)
	{
		printf("It is stil alive with %dhp!\n", monster->hit_points);
		return 0;
	}
	else
	{
		printf("It is dead!\n");
		return 1;
	}
}

int Monster_init(void *self)
{
	Monster *monster = self;
	monster->hit_points = 10;
	return 1;
}

Object MonsterProto = { .init = Monster_init, .attack = Monster_attack };

/**************************************************************************
	Room functions
**************************************************************************/

void *Room_move(void *self, Direction direction)
{
	Room *room = self;
	Room *next = NULL;

	if (direction == NORTH && room->north)
	{
		printf("You go north into:\n");
		next = room->north;
	}
	else if (direction == SOUTH && room->south)
	{
		printf("You go south into:\n");
		next = room->south;
	}
	else if (direction == WEST && room->west)
	{
		printf("You go west into:\n");
		next = room->west;
	}
	else if (direction == EAST && room->east)
	{
		printf("You go east into:\n");
		next = room->east;
	}
	else
	{
		printf("You can't go there.\n");
	}

	if (next != NULL)
	{
		next->_(describe)(next);
	}

	return next;
}

int Room_attack(void *self, int damage)
{
	Room *room = self;
	Monster *monster = room->bad_guy;

	if (monster != NULL)
	{
		monster->_(attack)(monster, damage);
		return 1;
	}
	else
	{
		printf("You flail into air. Idiot.\n");
		return 0;
	}
}

Object RoomProto = { .move = Room_move, .attack = Room_attack };

/**************************************************************************
	Map functions
**************************************************************************/

void *Map_move(void *self, Direction direction)
{
	Map *map = self;
	Room *room = map->location;
	Room *next = NULL;

	next = room->_(move)(room, direction);

	if (next != NULL)
	{	
		map->location = next;
	}

	return next;
}

int Map_attack(void *self, int damage)
{
	Map *map = self;
	Room *location = map->location;

	return location->_(attack)(location, damage);
}

int Map_init(void *self)
{
	Map *map = self;

	// make some rooms for a small map
	Room *hall 		= NEW(Room, "The great Hall");
	Room *throne 	= NEW(Room, "The throne room");
	Room *arena 	= NEW(Room, "The arena wiht the minotaur");
	Room *kitchen 	= NEW(Room, "Kitchen, you have the knife now");

	// put the bad guy in the arena
	arena->bad_guy = NEW(Monster, "The evil minotaur");

	// setup the map rooms

	hall->north = throne;

	throne->west = arena;
	throne->east = kitchen;
	throne->south = hall;

	arena->east = throne;

	kitchen->west = throne;

	map->start = hall;
	map->location = hall;

	return 1;
}

Object MapProto = { .init = Map_init, .move = Map_move, .attack = Map_attack };

/**************************************************************************
	Map functions
**************************************************************************/

int process_input(Map *game)
{
	printf("\n> ");

	char ch = getchar();
	getchar(); // process Enter

	int damage;

	switch(ch)
	{
		case '0':
			printf("Giving up? You suck!\n");
			return 0;

		case 'n':
			game->_(move)(game, NORTH);
			break;

		case 's':
			game->_(move)(game, SOUTH);
			break;

		case 'w':
			game->_(move)(game, WEST);
			break;

		case 'e':
			game->_(move)(game, EAST);
			break;

		case 'a':
			damage = rand() % 4;
			game->_(attack)(game, damage);
			break;

		case 'l':
			printf("You can go next directions:\n");
			if (game->location->north) printf("NORTH ");
			if (game->location->south) printf("SOUTH ");
			if (game->location->east)  printf("EAST ");
			if (game->location->west)  printf("WEST");
			printf("\n");
			break;

		default:
			printf("No such command.\n");
	}

	return 1;
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	Map *game = NEW(Map, "The Castle of Minotaur");

	printf("You enter the ");
	game->location->_(describe)(game->location);

	int running = 1;

	while (running)
	{

		running = process_input(game);
	}

	printf("Game over.\n");

	return 0;
}























