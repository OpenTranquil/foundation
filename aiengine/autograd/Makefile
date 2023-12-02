CC = gcc

CFLAGS=-c -Wall
LDFLAGS=

OBJS = grad.o main.c

all: grad

grad:	$(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o grad

*.o: *.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm -rf grad