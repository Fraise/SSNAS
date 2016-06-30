CC=gcc
CFLAGS=-W -Wall -pedantic -lssl -lcrypto
LDFLAGS=-W -Wall -pedantic -lssl -lcrypto
EXEC=SNASS

all: $(EXEC)

SNASS: main.o
	$(CC) -o SNASS main.o $(LDFLAGS)

main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
