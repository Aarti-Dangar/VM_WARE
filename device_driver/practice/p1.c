#include<stdio.h>
int main()
{
	FILE *file;
	char buffer[100];
	file=fopen("p1.txt","r");
	if(file==NULL)
	{
		perror("Error opening file");
		return -1;
	}
	fgets(buffer,100,file);
	printf("Read form file :%s",buffer);
	fclose(file);
	return 0;
}
