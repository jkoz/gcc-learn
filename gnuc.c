#include <math.h>
#include <stdio.h>

/*should compile with glibc (without -ansi)*/
/*gcc gnuc.c*/

/*if we want use -ansi, we have to define a special macro such as _GNU_SOURCE*/
/*gcc -ansi -D_GNU_SOURCE gnuc.c*/

/*if we want use -std=c99, we have to define a special macro such as _GNU_SOURCE*/
/*gcc -std=c99 -D_GNU_SOURCE gnuc.c*/

/*gcc -std=gnu99 gnuc.c*/

int
main (void)
{
	printf("the value of pi is %f\n", M_PI);
	return 0;
}
