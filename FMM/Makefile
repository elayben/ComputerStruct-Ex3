CC = gcc
CFLAGS = -g -O3
NOCOMPILE = -c

.PHONY: all clean

all: fmm clean

fmm: main.o fmm.o utilities.o
	$(CC) $(CFLAGS) $^ -o $@

utilities.o: utilities.c fmm.h
	$(CC) $(CFLAGS) $(NOCOMPILE) utilities.c -o utilities.o

main.o: main.c fmm.h
	$(CC) $(CFLAGS) $(NOCOMPILE) main.c -o main.o

fmm.o: fmm.c fmm.h
	$(CC) $(CFLAGS) $(NOCOMPILE) fmm.c -o fmm.o

clean:
	rm -f *.o