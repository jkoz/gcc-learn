#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
	int *data;
	struct Element *next;
} Element;

// Stack is a pointer to a pointer to the head of the list
// Why ** ? the reason is we have to update the pointer to the head of the list
// to new value
// IMPORTANT: every value pass to func is copied
int push(Element **, int *);
int pop(Element **, int **);
int createStack(Element **);
int deleteStack(Element **);
int printStack(Element **);

void main() {
	Element *stack;
	createStack(&stack);

	int v1 = 19, v2 = 21, v3 = 11, v4 = 24;

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

	deleteStack(&stack);
}

int createStack(Element **stack) {
	*stack = NULL;
	return 0;
}

int push(Element **stack, int *data) {
	Element *ptr = (Element*) malloc(sizeof (Element*));
	if (!ptr) return 1; // ptr is NULL

	ptr->data = data;
	ptr->next = *stack;

	*stack = ptr;
	return 0;
}

int pop(Element **stack, int **data) {
	Element *ptr = *stack;
	if (!ptr) return 1; // ptr is NULL

	*stack = ptr->next; // keep track next node
	*data = ptr->data; // get data

	free(ptr);
	return 0;
}

int deleteStack(Element **stack) {
	Element *next;
	while(*stack) {
		next = (*stack)->next; // keep next node of the current node
		free(*stack); // free current node
		*stack = next; // assign stack to the next node
	}
	return 0;
}

int printStack(Element **stack) {
	printf("printStack: \n");
	while (*stack) {
		printf("Data: %d\n", *((*stack)->data));
		stack = &((*stack)->next);
	}
}
