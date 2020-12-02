CC = gcc
CFLAGS = -Wall -Wextra -g

all: myavl
	
myavl: main.c avl.o
	$(CC) main.c avl.o -o myavl $(CFLAGS)

avl.o: avl.h avl.c

clean:
	rm -f *.o

purge: clean 
	rm -f myavl