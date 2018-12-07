CC = gcc -Wall
CFLAGS = -I/usr/include -D_REENTRANT -L/usr/lib -Wl,-rpath,/usr/lib -lm
LDFLAGS = -lSDL -lpthread -lGL -lGLU

all: clean main

main:
	$(CC) $(CFLAGS) $(LDFLAGS) main.c -o $@

circle:	clean
	$(CC) $(CFLAGS) $(LDFLAGS) circle.c -o $@

circles: clean
	$(CC) $(CFLAGS) $(LDFLAGS) circles.c -o $@

crap: clean
	$(CC) $(CFLAGS) $(LDFLAGS) crap.c -o $@

clean:
	rm -rf *.o main circle

