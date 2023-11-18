CC     = gcc
CFLAGS = -O2 -std=c99 -pedantic -Wall

main: main.c phasor.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f main
