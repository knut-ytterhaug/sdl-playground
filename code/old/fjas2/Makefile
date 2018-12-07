CC = gcc -Wall
CFLAGS = -I/usr/include -D_REENTRANT -L/usr/lib -Wl,-rpath,/usr/lib
LDFLAGS = -lSDL -lpthread 

all: clean main

main:
	$(CC) $(CFLAGS) $(LDFLAGS) main.c -o $@

clean:
	rm -rf *.o main
