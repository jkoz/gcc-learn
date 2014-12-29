#include <string.h>
#define _GNU_SOURCE //asks stdio.h to include asprintf
#include <stdio.h>


typedef struct ok_array {
	char **elements;
	char *base_string;
	int length;
} ok_array;

ok_array *ok_array_new(char *instring, char const *delimiters);

void ok_array_free(ok_array *ok_in);
