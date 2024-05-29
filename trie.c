#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readline(FILE* fp, char* output_buffer) {
	//readline raw

	char tmp[256] = {0, };
	if (fgets(tmp, 256, fp) == NULL) {
		return 0;
	}
	int idx = 0;
	while(tmp[idx] != ',') {
		idx++;
	}

	strcpy(output_buffer, &tmp[idx+1]);

	return 1;
}

trie* csv_to_trie(const char* file_name) {
	char hostname[256] = { 0, };
	FILE* fp = fopen(file_name, "r");
	trie* root = (trie*)malloc(sizeof(trie));

	//initialize
	root->fd = NULL;
	root->bk = NULL;
	root->data = 0;
	root->children = NULL;
	while (readline(fp, hostname)) {
		int idx = 0;
		trie* cur = root;
		do {
			trie* tmp;
			search_children(cur, hostname[idx], &tmp, 0);
			if (tmp == NULL) {
				trie* new_node = (trie*)malloc(sizeof(trie));
				new_node->fd = NULL;
				new_node->bk = cur->children;
				new_node->children = NULL;
				new_node->data = hostname[idx];

				// insert node
				if (cur->children)
					(cur->children)->fd = new_node;
				cur->children = new_node;
				tmp = new_node;
			}
			cur = tmp;
			idx++;
		} while(hostname[idx] != 0);
		//printf("%s", hostname);
		//printf("%d\n", idx);
		//print_trie(root);
		memset(hostname, 0, 256);
	}
	return root;
}

bool search_hostname(const char* hostname, trie* black_list) {
	trie* cur = black_list;
	int idx = 6;
	printf("%s\n", hostname);
	//print_trie(black_list);

	while(1) {
		printf("hostname[%d]: %d\n", idx, hostname[idx]);
		trie* tmp;
		search_children(cur, hostname[idx], &tmp, 1);
		if (tmp == 0) {
			//printf("return");
			return 1;
		}
		else {
			//printf("tmp->data: %d\n", tmp->data);
			if (hostname[idx + 1] == '\n' || hostname[idx+1] == ' ') {
				trie* tmp0;
				search_children(cur->children, '\n', &tmp0, 1);
			}
			else {
				idx++;
				cur = tmp;
				continue;
			}
		}
	}

	return 2;
}

void search_children(trie* parent, char data, trie** output, int flag) {
	trie* cur = parent->children;
	//if (flag) {
		//printf("hihello\n");
		//printf("%p\n", cur);
	//}

	while (cur != NULL) {
		if (flag) {
			//printf("go ");
			//printf("%c\n", cur->data);
		}
		if (cur->data == data) {
			break;
		}
		cur = cur->bk;
	}
	//if (flag)
	//	printf("%llx\n", cur);
	*output = cur;
}

void print_trie(trie* root) {
	trie* child = root->children;

	if (child == NULL) {
		printf("No children\n");
	}
	else {
		printf("children addr %p\n", child);
	}
	while(child) {
		printf("%d ", child->data);
		child = child->bk;
	}
	printf("\n");
	int idx;
	scanf("%d", &idx);

	if (idx != 100) {
		print_trie(root->children);
	}
	return;
}