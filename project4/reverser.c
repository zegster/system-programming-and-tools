//----------------------------------------------------------------------------------------------------
//Author:	Duc Ngo
//Course:	CS2750-001
//Name:		reverser.c
//Purpose:	Read in a text file based on a command line argument
//			and then work with that file, producing an output file (see Project #4 for more info)
//----------------------------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "stack.h"

int main(int argc, char *argv[])
{	
	//Default input and output file name
	char inputfile[256] = "input.txt";
	char outputfile[256] = "output.txt";
	
	//Options
	int opt;
	while((opt = getopt(argc, argv, "hi:o:")) != -1)
	{
		switch(opt)
		{
			case 'h':
				printf("NAME:\n");
				printf("	%s - read in a text file based on a command line argument\n", argv[0]);
				printf("	and then work with that file, producing an output file.\n");
				printf("\nUSAGE:\n");
				printf("	%s\n", argv[0]);
				printf("	%s -i <file1.txt> -o <file2.txt>\n", argv[0]);
				printf("	%s -i <file1.txt>\n", argv[0]);
				printf("	%s -o <file2.txt>\n", argv[0]);
				printf("\nDESCRIPTION:\n");
				printf("	[No Option]	: take in default file (input.txt) and outputing default file (output.txt)\n");
				printf("	-h		: display help page\n");
				printf("	-i <file1.txt>	: take in and running the specify input file.\n");
				printf("	-o <file2.txt>	: specify the output file.\n\n");
				return EXIT_FAILURE;

			case 'i':
				strncpy(inputfile, optarg, 255);
				printf("Your new input file is: %s\n", inputfile);
				break;
			
			case 'o':
				strncpy(outputfile, optarg, 255);
				printf("Your new output file is: %s\n", outputfile);
				break;

			default:
				printf("ERROR: please use \"-h\" option for more info.\n");
				return EXIT_FAILURE;
		}
	}
	
	//Check for extra arguments
	if(optind < argc)
	{
		printf("ERROR: extra arguments detected! Please use \"-h\" option for more info.\n");
		return EXIT_FAILURE;
	}
	
	//Create a stack and initialize it
	Stack stk;
        initialize(&stk);

	//Check if read/write a file is possible
	FILE *fpr;
	FILE *fpw;
	fpr = fopen(inputfile, "r");
	fpw = fopen(outputfile, "w");
	if(fpr == NULL)
	{
		printf("ERROR: unable to read the input file. Please check if the input file exist.\n");
		return EXIT_FAILURE;
	}
	if(fpw == NULL)
	{
		printf("ERROR: unable to write the output file.\n");
		return EXIT_FAILURE;
	}
	
	//Insert to stack procedure
	char data[100];
	char *token;
	int num;
	int in;
	while(fgets(data, (sizeof(data) - 1), fpr) != NULL)
	{
		//Check for duplicate element
		token = strtok(data, " \t,.-");
		while(token != NULL)
		{
			in = atoi(token);
			if(isDuplicate(&stk, in) == 0)
			{
				push(&stk, in);
			}
			token = strtok(NULL, " \t,.-");
		}
		
		//Pop procedure and write to the output file
		while(peek(&stk) != -1)
		{
			num = pop(&stk);
			fprintf(fpw, "%d", num);
			if(peek(&stk) != -1)
			{
				fprintf(fpw, " ");
			}
		}
		fprintf(fpw, "\n");
	}
	fclose(fpr);		
	fclose(fpw);

	printf("Done...\n");
	return EXIT_SUCCESS;
}
