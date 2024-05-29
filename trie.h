#include <stdbool.h>
#include <stdio.h>

typedef struct linked_list{
	struct linked_list* fd;
	struct linked_list* bk;
	
	struct linked_list* children;
	char data;						// if data == 10('\n')si, then it is leaf node
} trie;

//parse csv file and make trie data structure
trie* csv_to_trie(const char* file_name);

//search hostname in trie
//0 return when blacklist detected
bool search_hostname(const char* hostname, trie* black_list);

//read csv file line by line
//EOF -> return 0
int readline(FILE* fp, char* output_buffer);

//return children trie structure, if return NULL -> no search result
void search_children(trie* parent, char data, trie** output, int flag);

void print_trie(trie* root);