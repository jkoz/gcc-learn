#include <stdio.h>
#include <stdlib.h>

// not correct if x is manually allocated
#define LENGTH(x) sizeof(x)/sizeof(x[0])

#define Peval(cmd) printf(#cmd ": %d\n", cmd)

struct inner_node {
	int in_a;
	int in_b;
};

struct node{
	int *a;
	int *b;
	struct inner_node* in_node;
};

int main() {
	printf("\nAutomic automicMem[50]\n");
	int automicMem[50];
	Peval(sizeof(automicMem[0])); /* size of integer is 4 bytes */
	Peval(sizeof(automicMem)); /* size of 'automic array' on stack is 200 bytes */
	Peval(LENGTH(automicMem));

	printf("\n");
	printf("Manually allocating 50*sizeof(int):\n");
	int *manuallyMem = malloc(sizeof(int) * 50);
	Peval(sizeof(manuallyMem[0])); /* size of integer is 4 bytes */
	Peval(sizeof(manuallyMem)); /* size of pointer on stack is 8 bytes */
	Peval(LENGTH(manuallyMem)); /* INCORRECT, expect 50, however it shows 2 */

	printf("\n");
	printf("Size of pointers are same!\n");
	Peval(sizeof(char*)); /* 8 */
	Peval(sizeof(double*)); /* 8 */
	Peval(sizeof(int*)); /* 8 */
	Peval(sizeof(struct node*)); /* 8 */

	printf("\n");
	printf("Size of pointer variables are same too!\n");
	char _char = 1, *char_ptr = &_char; Peval(sizeof(char_ptr));/* 8 */
	int _int = 1, *int_ptr = &_int; Peval(sizeof(int_ptr));/* 8 */
	float _float = 1, *float_ptr = &_float; Peval(sizeof(float_ptr));/* 8 */
	struct node _node, *node_ptr = &_node; Peval(sizeof(node_ptr));/* 8 */

	printf("\n");
	printf("Size of array pointer variables are same too!!\n");
	int *array_ptr = &automicMem[0]; Peval(sizeof(array_ptr)); /* 8 */
	float array_float[2], *array_float_ptr = array_float; Peval(sizeof(array_float_ptr)); /* 8 */
	struct node array_node[2], *array_node_ptr = array_node; Peval(sizeof(array_node_ptr)); /* 8 */

	printf("\n");
	printf("Size of struct variables are DIFFERENT\n");
	Peval(sizeof(struct node)); // 24 = 8 + 8 + 8
	Peval(sizeof(struct inner_node)); // 8 = 4 + 4

	printf("\n");
	printf("Size of types are DIFFERENT\n");
	Peval(sizeof(int));
	Peval(sizeof(short int));
	Peval(sizeof(float));
	Peval(sizeof(double));
	Peval(sizeof(char));
	Peval(sizeof(short));
	Peval(sizeof(long));
	Peval(sizeof(unsigned int));
	Peval(sizeof(unsigned long));
	Peval(sizeof(long int));
	Peval(sizeof(long long));


	return 0;
}
