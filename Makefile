# CFLAGS =

all: aDev

aDev: aDev.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	-rm -f aDev *.o
