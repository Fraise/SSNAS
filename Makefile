CC=gcc
CFLAGS=-W -Wall -pedantic -lssl -lcrypto
LDFLAGS=-W -Wall -pedantic -lssl -lcrypto
EXEC=SNASS

all: $(EXEC)

SNASS: main.o ssl.o
	$(CC) -o SNASS main.o ssl.o $(LDFLAGS)

main.o: main.c ssl.h
	$(CC) -o main.o -c main.c $(CFLAGS)

ssl.o: ssl.c
	$(CC) -o ssl.o -c ssl.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
