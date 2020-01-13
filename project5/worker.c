//----------------------------------------------------------------------------------------------------
//Author:	Duc Ngo
//Course:	CS2750-001
//Name:		worker.c
////Purpose:	Read in given number and find the biggest prime less than a given number. Then save
//		it to the share memory.
//----------------------------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 384698

int prime(int num);

int main(int argc, char *argv[])
{
	printf("%s: running...\n", argv[0]);

	//Default-Storage Variable
	key_t key = SHMKEY;
	int number = 100;

	//Option
	int opt;
	while((opt = getopt(argc, argv, "n:")) != -1)
	{
		switch(opt)
		{
			case 'n':
				if(atoi(optarg) != 0)
				{
					number = atoi(optarg);
				}
				else
				{
					fprintf(stderr, "%s ERROR: non integer was given! Exiting...\n", argv[0]);
					return EXIT_FAILURE;
				}
				break;

			default:
				fprintf(stderr, "%s ERROR: please use -n option follow by an integer.\n", argv[0]);
				return EXIT_FAILURE;
		}
	}

	//Check for extra arguments
	if(optind < argc)
	{
		fprintf(stderr, "%s ERROR: extra arguments detected! Please use \"-h\" option for more info.\n", argv[0]);
		return EXIT_FAILURE;
	}

	//Get shmid from already alocated memory
	int shmid;
	if((shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < 0)
	{
		fprintf(stderr, "%s ERROR: could not get shared memory ID! Exiting...\n", argv[0]);
		return EXIT_FAILURE;
	}

	//Attaching shared memory
	int *shmptr;
	if((shmptr = (int *)shmat(shmid, NULL, 0)) == (int *)( -1 ))
	{
		fprintf(stderr, "%s ERROR: fail to attach! Exiting...\n", argv[0]);
		return EXIT_FAILURE;
	}

	//Check to see if value in shared memory is zero
	if(*shmptr == 0)
	{
		printf("%s: zero detected! Finding the biggest prime less than the given number.\n", argv[0]);
	}
	else
	{
		fprintf(stderr, "%s ERROR: value in shared memory is not zero! Exiting...\n", argv[0]);
		return EXIT_FAILURE;
	}

	//Find the largest prime less than the given number procedure
	*shmptr = prime(number);
	printf("%s: best result found! Waiting for master...\n", argv[0]);
	
	//Waiting for master: break the loop when value in shared memory is zero or after 60 seconds
	int timer = 0;
	while(*shmptr != 0)
	{
		timer++;
		sleep(1);
		if(timer >= 60)
		{
			fprintf(stderr, "%s ERROR: something went wrong! The task took longer than it suppose to. Aborting...\n", argv[0]);
			return EXIT_FAILURE;
		}
	}
	printf("%s: zero detected! Task is sucessful.\n", argv[0]);
	
	//Detach shared memory
	shmdt(shmptr);
	printf("%s: DONE...\n", argv[0]);
	return EXIT_SUCCESS;
}

int prime(int num)
{
	int biggest;
	int i, j, isPrime;

	if(num <= 1)
	{
		return -1;
	}

	for(i = 2; i <= num; i++)
	{
		isPrime = 1;
		for(j = 2; j < i; j++)
		{
			if(i % j == 0)
			{
				isPrime = 0;
				break;
			}	
		}
	
		if(isPrime)
		{
			biggest = i;
		}
	}
	return biggest;
}
