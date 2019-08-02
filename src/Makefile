CFLAGS = -Wall -Wextra

OBJS = main.o parser.o commands.o find_and_union.o trie.o

all: $(OBJS)
	gcc $(CFLAGS) -o quantization $(OBJS)

find_and_union.o: find_and_union.c

trie.o: trie.c

commands.o: find_and_union.h trie.h

parser.o: commands.h find_and_union.h trie.h

main.o: parser.h commands.h find_and_union.h trie.h

.PHONY: clean
clean:
	rm -f $(OBJS) quantization

