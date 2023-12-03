CC = gcc

CFLAGS=-c -Wall
LDFLAGS=

OBJS_AUTOGRAD = autograd/grad.o tensor/tensor.c main.c

all: grad

grad:	$(OBJS_AUTOGRAD)
	$(CC) $(LDFLAGS) $(OBJS_AUTOGRAD) -o grad

*.o: *.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf autograd/*.o
	rm -rf grad