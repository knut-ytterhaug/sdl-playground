CC = gcc -Wall
CFLAGS = -I/usr/include -D_REENTRANT -L/usr/lib -Wl,-rpath,/usr/lib  -lm
LDFLAGS = -lSDL 

all: clean main

main:
	$(CC) $(CFLAGS) $(LDFLAGS) main.c -o $@

clean:
	rm -rf *.o main
