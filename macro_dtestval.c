#include <stdio.h>

/*need provde define in gcc*/
/*gcc -Wall -DNUM=10 macro_dtestval.c*/
/*gcc -Wall -DNUM="10+2" macro_dtestval.c*/
/*gcc -Wall -DNUM macro_dtestval.c*/

int
main (void)
{
	printf("Value of NUM is %s\n", NUM);
	return 0;
}
