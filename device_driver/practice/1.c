#include<stdio.h>
#include<stdlib.h>
int main()
{

	FILE *file=fopen("config.txt","r");
	if(!file)
	{
		perror("Failed to open config.txt");
		return EXIT_FAILURE;
	}
	fclose(file);
	return EXIT_SUCCESS;
}
