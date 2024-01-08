CC     = gcc
CFLAGS = -std=c99 -pedantic -Wall -O2
TFLAGS = -std=c99 -pedantic -Wall -g
LIBS   = -lm

MAIN   = main.c signals.c
TEST   = test.c signals.c

main: $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

test: $(TEST)
	$(CC) $(TFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f main test
