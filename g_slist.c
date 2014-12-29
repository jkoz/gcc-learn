#include <stdio.h>
#include <stdlib.h>

typedef struct node_t{
	int *data;
	struct Node *next;
} node_t;

int insertHead(node_t**, int*);
int insertAfter(node_t**);
int insertBefore(node_t**);


