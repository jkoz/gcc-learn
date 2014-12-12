#include <stdio.h>

/*run with test mode*/
/*gcc -Wall -DTEST macro_dtest.c*/

int
main (void)
{
#ifdef TEST
	printf ("Test mode\n");
#endif
	printf ("Running...\n");
	return 0;
}
