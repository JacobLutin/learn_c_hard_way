#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 1024

struct Record
{
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_ROWS];
};

struct Connection
{
	FILE *file;
	struct Database *db;
};

struct Database
{
	struct Record rows[MAX_ROWS];
};

void die(const char *message)
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

void Record_print(struct Record *record)
{
	printf("%d %s %s\n", record->id, record->name, record->email);
}

void Database_connect(struct Connection *connection)
{
	// printf("%p\n", malloc(size_of(connection->db));
	// printf("%p\n", realloc(struct Database));
	int rc = fread(connection->db, sizeof(struct Database), 1, connection->file);
	// if (rc != 1) 
		// die("Failed to load database.");
}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *connection = malloc(sizeof(struct Connection));
	if (connection == NULL) 
		die("Memory error.");

	connection->db = malloc(sizeof(struct Database));
	if (connection->db == NULL) 
		die("Memory error.");

	if (mode == 'c')
	{
		connection->file = fopen(filename, "w");
	}
	else
	{
		connection->file = fopen(filename, "r+");

		if (connection->file) 
		{
			Database_connect(connection);
		}

	}

	if (connection->file == NULL)
			die("Failed to open file");

	return connection;
}

void Database_close(struct Connection *connection) 
{
	if (connection != NULL) 
	{
		if (connection->file != NULL)
			fclose(connection->file);

		if (connection->db != NULL)
			free(connection->db);
		
		free(connection);
	}
}

void Database_write(struct Connection *connection)
{
	if (connection == NULL)
		die("Memory error.");

	rewind(connection->file);

	int rc = fwrite(connection->db, sizeof(struct Database), 1, connection->file);
	if (rc != 1)
		die("Failed to write database.");

	rc = fflush(connection->file);
	if (rc == EOF)
		die("Cannot flush database.");
}

void Database_create(struct Connection *connection)
{
	int i;

	for (i = 0; i < MAX_ROWS; i++)
	{
		struct Record record = {.id = i, .set = 0};
		connection->db->rows[i] = record;
	}
}

void Database_set(struct Connection *connection, int id, const char *name, const char *email)
{
	struct Record *record = &connection->db->rows[id];
	if (record->set == 1) 
		die("Record is already created.");

	char *res = strncpy(record->name, name, MAX_DATA);
	if (!res)
		die("Name copy failed.");

	res = strncpy(record->email, email, MAX_DATA);
	if (!res)
		die("Email copy failed.");
}

void Database_get(struct Connection *connection, int id)
{
	struct Record *record = &connection->db->rows[id];

	if (record->set == 1)
	{
		Record_print(record);
	}
	else
		die("ID error.");
}

void Database_delete(struct Connection *connection, int id)
{
	struct Record record = {.id = id, .set = 0};
	connection->db->rows[id] = record;
}

void Database_list(struct Connection *connection)
{
	int i;

	for (i = 0; i < MAX_ROWS; i++)
	{
		struct Record *record = &connection->db->rows[i];

		if (record->set == 1)
		{
			Record_print(record);
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
		die("USAGE: ./ex17 <dbfile> <action> [action params]");

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *connection = Database_open(filename, action);
	int id = 0;

	if (argc > 3)
		id = atoi(argv[3]);

	if (id > MAX_ROWS)
		die("There is not that many records.");

	switch (action)
	{
		case 'l':
			Database_list(connection);
			break;
		case 'g':
			Database_get(connection, id);
			break;
		default:
			die("No action key.");
	}

	Database_close(connection);
	
	return 0;

}



























