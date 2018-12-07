CC = gcc -Wall
LDFLAGS = -lSDL

all: clean main

clean:
	@rm -rf *.o main

hsv.o:
	$(CC) $(CFLAGS) hsv.c -o $@ -c

main.o:
	$(CC) $(CFLAGS) main.c -o $@ -c

main: main.o screen.o hsv.o
	$(CC) $(LDFLAGS) hsv.o screen.o main.o -o $@

screen.o:
	$(CC) $(CFLAGS) screen.c -o $@ -c
