reverser:	reverser.o stack.o
	gcc -g -o reverser reverser.o stack.o

reverser.o:	reverser.c stack.h
	gcc -g -c reverser.c

stack.o:	stack.c stack.h
	gcc -g -c stack.c

.PHONY: clean
clean:
	/bin/rm -f *.o reverser
