#include <stdio.h>
#include <unistd.h>

int main()
{
	int i = 0;
	
	while (1)
	{
		fprintf(stdout, "\r%d", i);
		
		//fflush(stdout);

		sleep(1);

		i++;
	}

	return 0;
}
