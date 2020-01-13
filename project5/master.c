//----------------------------------------------------------------------------------------------------
//Author:	Duc Ngo
//Course:	CS2750-001
//Name:		main.c
//Purpose:	Create some shared memory and then launch a user process (using fork and exec)
//		to do some work. 
//----------------------------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h> 
#define SHMKEY 384698

int main(int argc, char *argv[])
{
	printf("\n%s (parent): running...\n", argv[0]);	

	//Default-Storage Variable
	key_t key = SHMKEY;
	int number = 100;
	char enumber[15] = "100";

	//Options
	int opt;
	while((opt = getopt(argc, argv, "hn:")) != -1)
	{
		switch(opt)
		{
			case 'h':
				printf("NAME:\n");
				printf("	%s - read in given number and find the largest prime number less than given number.\n", argv[0]);
				printf("\nUSAGE:\n");
				printf("	%s\n", argv[0]);
				printf("	%s -n <integer number>\n", argv[0]);
				printf("\nDESCRIPTION:\n");
				printf("	[No Option]		: find the largest prime number less than given default number (100).\n");
				printf("	-h			: display help page\n");
				printf("	-n <integer number>	: take in given number and find the largest prime number less than it.\n\n");
				return EXIT_FAILURE;

			case 'n':
				strcpy(enumber, optarg);
				if(atoi(optarg) != 0)
				{
					number = atoi(optarg);
				}
				else
				{
					fprintf(stderr, "%s (parent) ERROR: non integer was given! Exiting...\n", argv[0]);
					return EXIT_FAILURE;
				}
				break;

			default:
				fprintf(stderr, "%s (parent) ERROR: please use \"-h\" option for more info.\n", argv[0]);
				return EXIT_FAILURE;
		}
	}

	//Check for extra arguments
	if(optind < argc)
	{
		fprintf(stderr, "%s (parent) ERROR: extra arguments detected! Please use \"-h\" option for more info.\n", argv[0]);
		return EXIT_FAILURE;
	}

	//Print out given number
	printf("%s (parent): your given number is: %d\n", argv[0], number);
	
	//Allocate shared memory
	int shmid;
	if((shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < 0)
	{
		fprintf(stderr, "%s (parent) ERROR: could not allocate shared memory! Exiting...\n", argv[0]);
		return EXIT_FAILURE;
	}

	//Attaching shared memory
	int *shmptr;
	if((shmptr = (int *)shmat(shmid, NULL, 0)) == (int *)( -1 ))
	{
		fprintf(stderr, "%s (parent) ERROR: fail to attach! Exiting...\n", argv[0]);
		if((shmctl(shmid, IPC_RMID, NULL)) < 0)
		{
			fprintf(stderr, "%s (parent) ERROR: could not delete allocate shared memory! Exiting...\n", argv[0]);
		}
		return EXIT_FAILURE;	
	}
	//Initialize value in shared memory 
	*shmptr = 0;
	printf("%s (parent): initialized zero in shared memory.\n", argv[0]);
	
	//Fork procedure -> child (exec the worker) -> parent (read the biggest prime from shm that worker write to)
	//Check if fork is unsuccessful
	int pid = fork();
	if(pid == -1)
	{
		fprintf(stderr, "%s (parent) ERROR: failed to fork! Exiting...", argv[0]);
		if((shmctl(shmid, IPC_RMID, NULL)) < 0)
		{
			fprintf(stderr, "%s (parent) ERROR: could not delete allocate shared memory! Exiting...\n", argv[0]);
		}
		return EXIT_FAILURE;
	}
	
	//Child
	if(pid == 0)
	{	
		int exStatus = execl("./worker", "./worker", "-n", enumber, NULL);
		if(exStatus == -1)
        	{	
			fprintf(stderr, "%s (parent) ERROR: execl fail to execute! Exiting...\n", argv[0]);
		}
		return EXIT_FAILURE;
	}
	//Parent
	else
	{
		//Waiting for worker: break the loop when value in shared memory is not zero or after 60 seconds
		printf("%s (parent): waiting for worker...\n", argv[0]);
		int timer = 0;
		while(*shmptr == 0)
		{
			timer++;
			sleep(1);
			if(timer >= 60)
			{		
				fprintf(stderr, "%s (parent) ERROR: something went wrong! The task took longer than it suppose to. Aborting...\n", argv[0]);
				if((shmctl(shmid, IPC_RMID, NULL)) < 0)
				{
					fprintf(stderr, "%s (parent) ERROR: could not delete allocate shared memory! Exiting...\n", argv[0]);
				}
				return EXIT_FAILURE;
			}
		}
		printf("%s (parent): result updated! Reading result...\n", argv[0]);

		//Output appropriate result
		if(*shmptr == -1)
		{
			printf("%s (parent): the given number is less than the biggest prime number (2).\n", argv[0]);
		}
		else if(*shmptr == number)
		{
			printf("%s (parent): the given number is already a prime: %d\n", argv[0], *shmptr);
		}
		else
		{
			printf("%s (parent): the biggest prime number less than a given number is: %d\n", argv[0], *shmptr);
		}

		//Set value in shared memory back to zero
		*shmptr = 0;
		printf("%s (parent): setting value in shared memory back to zero. Wating for worker...\n", argv[0]);

		//Waiting for worker to end
		int childStatus;	
		wait(&childStatus);
		if(childStatus != 0)
		{
			fprintf(stderr, "%s (parent) NOTICE: something went wrong in worker process!\n", argv[0]);
		}

		//Release shared memory
		if((shmdt(shmptr)) < 0)
		{
			fprintf(stderr, "%s (parent) ERROR: could not detach shared memory!\n", argv[0]);
		}
		printf("%s (parent): shared memory detached.\n", argv[0]);
		
		//Delete shared memory
		if((shmctl(shmid, IPC_RMID, NULL)) < 0)
		{
			fprintf(stderr, "%s (parent) ERROR: could not delete allocate shared memory! Exiting...\n", argv[0]);
			return EXIT_FAILURE;
		}
		printf("%s (parent): target shared memory deleted.\n", argv[0]);

		printf("%s (parent): DONE...\n", argv[0]);
		return EXIT_SUCCESS;
	}
}

