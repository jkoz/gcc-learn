#include<stdio.h>

/*complete warning: -W -Wall*/

int
foo (unsigned int x)
{
	if (x < 0)
		return 0;/* cannot occur */
	else
		return 1;
}

int
main() {
	pow(1.0, 2.0);
	return 0;
}
