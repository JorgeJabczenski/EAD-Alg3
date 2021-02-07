CC = gcc
CFLAGS = -Wall -Wextra -g

objs = main.c avl.o 

all: myavl
	
myavl: $(objs)
	$(CC) main.c avl.o -o myavl $(CFLAGS)

clean:
	rm -f *.o

purge: clean 
	rm -f myavl