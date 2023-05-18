CC = gcc
CFLAGS = -g -Wall

all: t9

t9: tnine.o trie.o
	$(CC) $(CFLAGS) -o t9 tnine.o trie.o

tnine.o: tnine.c trienode.h
	$(CC) $(CFLAGS) -c tnine.c

trie.o: trie.c trienode.h
	$(CC) $(CFLAGS) -c trie.c

clean:
	rm -f t9 tnine.o trie.o

