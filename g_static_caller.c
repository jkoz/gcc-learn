#include <stdio.h>

// x is being defined somewhere else
// the place defining x should be definend WITHOUT static keyword, otherwise compiler will raise error
// int x = 10;    OK
// static x = 10; NOTOK
extern int x;

extern void print_num();
extern void static_print_num();

void caller(void) {
	printf("global variable x=%d\n", x);
	printf("print_num()"); print_num();
	/*compile error*/
	/*printf("static_print_num()"); static_print_num();*/
}
