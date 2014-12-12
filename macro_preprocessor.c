#include<stdio.h>

#define TEST "hello, world"

/*to generate precompresssor files, run folllowing, and check macro_preprocessor.i*/
/*gcc -c -save-temps macro_preprocessor.c*/
/*or*/
/*cpp macro_preprocessor.c | vim -c 'set ft=c' - */


int
main() {
	printf("%s", TEST);
	return 0;
}
