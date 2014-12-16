#include <stdio.h>
#include <stdlib.h>

// gcc g_static.c g_static_caller.c

static int static_int; // [scope] this var is only access within this c file, cannot be accessed from other c files

int x = 10;
void caller(void);

static void static_print_num(); // this func is only access within this c file, cannot be accessed from other c files
void print_num();

int main() {
    static_print_num();
    static_print_num();
    static_print_num();

	print_num();
	print_num();
	print_num();

	caller();
}

static void static_print_num() {
	// extending [lifetime] of y to entire program, not only in stack of this func (stored in data of process)
	static int y = 0; // this only initialize one, after that, it skip this var
	printf("static_print_num: %d\n", y++);
}

void print_num() {
	int y = 0; // y is local var, stored in stack, will be discarded once finishing the func
	printf("print_num: %d\n", y++);
}
