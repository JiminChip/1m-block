1m-block: 1m-block.c trie.c trie.h
	gcc -o 1m-block 1m-block.c trie.c -lnetfilter_queue

clean:
	rm -f 1m-block