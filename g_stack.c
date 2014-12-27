#include <stdio.h>
#include <stdlib.h>

#define STACK_POP_PUSH 1
#define M_TO_LAST 0

struct Node {
	int *data;
	struct Node *next;
} *head;
typedef struct Node Node;

// Stack is a pointer to a pointer to the head of the list
// Why ** ? the reason is we have to update the pointer to the head of the list
// to new value
// IMPORTANT: every value pass to func is copied
int push(Node **, int *);
int pop(Node **, int **);
int createStack(Node **);
int deleteStack(Node **);
int printStack(Node **);

int initDummyStack(Node **, int*, int);
int findMToLastNode(Node **head, Node**, int m);

void main() {
	// pop operation
	Node *stack;
	createStack(&stack);

#if STACK_POP_PUSH
	int v1 = 19, v2 = 21, v3 = 11, v4 = 24;
	printf("Stack operations: \n");
	push(&stack, &v1);
	push(&stack, &v2);
	printStack(&stack);

	push(&stack, &v3);
	push(&stack, &v4);
	printStack(&stack);

	int *ret;
	printf("Popping...\n");
	pop(&stack, &ret);

	printStack(&stack);
	printf("Pop %d\n", *ret);
#else
	int d[] = { 19, 21, 11, 24, 15, 20 };
	initDummyStack(&stack, d, 6);
	printStack(&stack);

	Node *mBehind;
	findMToLastNode(&stack, &mBehind, 3);
	printf("3th behind the last node: %d", *(mBehind->data));
#endif

	deleteStack(&stack);
}

int initDummyStack(Node **stack, int *d, int size) {
	int i;
	for (i = 0; i < size; i++) {
		push(stack, &d[i]);
	}
	return 0;
}

int findMToLastNode(Node **head, Node **ret, int m) {
	Node *cur = *head;
	int i;
	for (i = 0; i < m; i++) {
		if (cur->next) {
			cur = cur->next;
		} else {
			return 1; // m is out of range of the list
		}
	}

	Node *mBehind = *head;
	while (cur->next) {
		cur = cur->next;
		mBehind = mBehind->next;
	}
	*ret = mBehind;

	return 0;
}

int createStack(Node **stack) {
	*stack = NULL;
	return 0;
}

int push(Node **stack, int *data) {
	Node *ptr = (Node*) malloc(sizeof (Node*));
	if (!ptr) return 1; // ptr is NULL

	ptr->data = data;
	ptr->next = *stack;

	*stack = ptr;
	return 0;
}

int pop(Node **stack, int **data) {
	Node *ptr = *stack;
	if (!ptr) return 1; // ptr is NULL

	*stack = ptr->next; // keep track next node
	*data = ptr->data; // get data

	free(ptr);
	return 0;
}

int deleteStack(Node **stack) {
	Node *next;
	while(*stack) {
		next = (*stack)->next; // keep next node of the current node
		free(*stack); // free current node
		*stack = next; // assign stack to the next node
	}
	return 0;
}

int printStack(Node **stack) {
	while (*stack) {
		printf("%d, ", *((*stack)->data));
		stack = &((*stack)->next);
	}
	printf("\n");
}
