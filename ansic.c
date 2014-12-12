#include <stdio.h>

/*should compile with ansi, because asm is a keyword in glibc */
/* gcc -ansi ansic.c*/

int
main (void)
{
	const char asm[] = "6502";
	printf ("the string asm is â%sâ\n", asm);
	return 0;
}
