//----------------------------------------------------------------------------------------------------
//Author:       Duc Ngo
//Course:       CS2750-001
//Name:         stack.h
//----------------------------------------------------------------------------------------------------
#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct stack
{
	int top;
	int stack[100];
} Stack;

void initialize(Stack *focus);
int peek(Stack *focus);
void push(Stack *focus, int num);
int pop(Stack *focus);
int isDuplicate(Stack *focus, int num);
#endif
