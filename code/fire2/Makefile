CC = gcc -Wall
LDFLAGS = -lSDL -lm

all: clean main

main:
	$(CC) $(CFLAGS) $(LDFLAGS) main.c -o $@

clean:
	rm -rf *.o main
