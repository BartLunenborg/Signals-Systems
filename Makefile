CC     = gcc
CFLAGS = -g3 -std=c99 -pedantic -Wall

main: main.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f main
