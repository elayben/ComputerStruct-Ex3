CC = gcc
CFLAGS = -g 

.PHONY: all clean
all: cache

cache: cache.o
	$(CC) $(CFLAGS) $^ -o $@ -no-pie

cache.o: cache.c
	$(CC) $(CFLAGS) -c cache.c

clean:
	rm -f *.o
