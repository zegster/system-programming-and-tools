//----------------------------------------------------------------------------------------------------
//Author:	Duc Ngo
//Course:	CS2750-001
//Name:		reverse.c
//Purpose:	Echos the command line arguments given it to stdout in reverse order and
//			display smallest and largest string (see project #3 for detail).
//----------------------------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Function Declaration
void line();

int main(int argc, char *argv[])
{
	line();
	//Check if command line args is empty
	if(argc < 2)
	{
		printf("Empty command line args!\n");
	}
	else
	{
		int i = argc - 1;
		printf("Number of args: %d\n", i);
		printf("Reverse command line args are: ");

		//Print reverse order of command line args 
		for(i = argc - 1; i > 0; i--)
		{
			printf("%s ", argv[i]);
		}
		printf("\n");

		//Search for the smallest and largest args (by lexographic order)
		int smallest = 1;
		int largest = 1;
		for(i = 1; i < argc; i++)
		{
			if(strcmp(argv[smallest], argv[i]) > 0)
			{
				smallest = i;
			}
			else if(strcmp(argv[largest], argv[i]) < 0)
			{
				largest = i;
			}
		}
		
		printf("The smallest string was: %s\n", argv[smallest]);
		printf("The largest string was: %s\n", argv[largest]);
	}
	line();
	return EXIT_SUCCESS;
}

//Function [line]
void line()
{
	int i = 0;
	int length = 75;
	for(i = 0; i < length; i++)
	{
		printf("=");
		if(i == length - 1)
			printf("\n"); 
	}
}
