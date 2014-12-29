#include <stdio.h>

/*global vars*/
int total;
int count;

int main() {
	/*init global vars*/
	total = 0;
	count = 0;
	{
		/*local var*/
		int count;
		count = 10;
		printf("%d\n", count);
	}
	count++;
	printf("%d\n", count);
}
