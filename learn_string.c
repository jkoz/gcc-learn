#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int
main () {
	char *str = strdup("abc");
	char *token = strtok(str, "@");
	printf("%s", token);
	/*free(str);*/
	free(token);
	return 0;
}
