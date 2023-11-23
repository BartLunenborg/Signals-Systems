CC     = gcc
CFLAGS = -g3 -std=c99 -pedantic -Wall

main: main.c sinusoid.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f main
