CC=gcc
CFLAGS=-Wall -Wextra -Wno-implicit-fallthrough -std=gnu17 -fPIC -O2 -g
LDFLAGS=-shared -Wl,--wrap=malloc -Wl,--wrap=calloc -Wl,--wrap=realloc -Wl,--wrap=reallocarray -Wl,--wrap=free -Wl,--wrap=strdup -Wl,--wrap=strndup

all: libseq.so

#Builds and links all needed components in order to create
#libseq.so library
libseq.so: trie.o memory_tests.o seq.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o libseq.so $^

trie.o: trie.c trie.h
	@$(CC) $(CFLAGS) -c trie.c

seq_example.o: seq_example.c seq.h memory_tests.h
	@$(CC) $(CFLAGS) -c seq_example.c

memory_tests.o: memory_tests.h memory_tests.c
	@$(CC) $(CFLAGS) -c memory_tests.c

seq.o: seq.c seq.h
	@$(CC) $(CFLAGS) -c seq.c

#Builds basic tests for libeseq.so library
tests: libseq.so seq_example.o
	$(CC) $(CFLAGS) -o tests -g seq_example.o -L. -lseq

#Cleans elements created during building and linking process
clean:
	rm -f libseq.so *.o



