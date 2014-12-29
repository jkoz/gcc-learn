#include<stdio.h>
#include <string.h>

int main () {
	if (1) {
		printf("if 1\n");
	}
	if (0) {
		printf("if 0\n");
	}
	if (!0) {
		printf("if !0\n");
	}
	if (2) {
		printf("if 2\n");
	}
	printf("Hello, world\n");

	char *b = "kien an ca";
	printf("%d", strlen(b));

	return 0;
}
