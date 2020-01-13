//----------------------------------------------------------------------------------------------------
//Author:	Duc Ngo
//Course:	CS2750-001
//Name:		stack.c
//----------------------------------------------------------------------------------------------------
#include "stack.h"

//----------------------------------------------------------------------------------------------------
//Set top counter to -1 and set all element in the stack to 0.
//----------------------------------------------------------------------------------------------------
void initialize(Stack *focus)
{
	focus->top = -1;
	
	int i = 0;
	int element = sizeof(focus->stack)/sizeof(focus->stack[0]);
	for(i = 0; i < element; i++)
	{
		focus->stack[i] = 0;
	}
}

//----------------------------------------------------------------------------------------------------
//Return the current top counter value.
//----------------------------------------------------------------------------------------------------
int peek(Stack *focus)
{
	return (focus->top);
}

//----------------------------------------------------------------------------------------------------
//Add new element to the stack and incrase top counter by one.
//----------------------------------------------------------------------------------------------------
void push(Stack *focus, int num)
{
	int element = sizeof(focus->stack)/sizeof(focus->stack[0]);
	if(focus->top == element - 1)
	{
		printf("Stack is full!\n");
		return;
	}
	else
	{
		focus->top = focus->top + 1;
		focus->stack[focus->top] = num;
	}
	return;
}

//----------------------------------------------------------------------------------------------------
//Return the top element of the stack and decrease top counter by one.
//----------------------------------------------------------------------------------------------------
int pop(Stack *focus)
{
	int num = -1;
	if(focus->top == -1)
	{
		printf("Stack is empty!\n");
		return (focus->top);
	}
	else
	{
		num = focus->stack[focus->top];
		focus->top = focus->top - 1;
	}
	return num;
}

//----------------------------------------------------------------------------------------------------
//Return true if there a duplicate number in the stack.
//----------------------------------------------------------------------------------------------------
int isDuplicate(Stack *focus, int num)
{
	int i = 0;
	int element = focus->top;
	for(i = 0; i <= element; i++)
	{
		if(focus->stack[i] == num)
		{
			return 1;
		}
	}
	return 0;
}
