#define _GNU_SOURCE /* cause stdio.h to include vasprintf */
#include <stdio.h>
#include <stdlib.h> /* free */
#include <string.h>

#define Sasprintf(write_to,  ...) {           \
	    char *tmp_string_for_extend = (write_to); \
	    asprintf(&(write_to), __VA_ARGS__);       \
	    free(tmp_string_for_extend);              \
	}

void get_strings_oldway(char const *in){
	/* 3 steps to clone to initialize a string */
	int len = strlen("strings ") + strlen(in) + 1; /* 1 is for terminator */
	char *cmd = malloc(len);
	snprintf(cmd, len, "strings %s", in);

	fprintf(stdout, "%s.\n", cmd);

	/* free is necessary */
	free(cmd);
}

/* if there is no strdup implemetaion, work with autotools: AC_CHECK_FUNCS([asprintf strdup])  */
#ifndef HAVE_STRDUP
char *strdup(char const* in){
	if (!in) return NULL;
	char *out;
	asprintf(&out, "%s", in);
	return out; /* out can be free, and modified */
}
#endif

void mem_leak_asprintf() {
	int col_number=3, person_number=27;

    /*NOT OK , free cause fail below Sasprintf*/
	char *q;

    /* fail with Sasprintf because it tries to free immutable string */
	q = "asdsad";

	/*free(NULL) cause segfault*/
	q = NULL;

	/* q should be initialize with strdup or set to null in order to use
 	   Sasprintf macro otherwise a segfault is raised*/
	q = strdup("select ");

	/*memory leak for each of following steps*/
	/*asprintf(&q, "%scol%i \n", q, col_number);*/
	/*asprintf(&q, "%sfrom tab \n", q);*/
	/*asprintf(&q, "%swhere person_id = %i", q, person_number);*/

	int i = 3;
	Sasprintf(q, "select * from tab");
	Sasprintf(q, "%s where col%i is not null", q, i);
	printf("%s\n", q);

	/* only free the last allocated memory */
    free(q);
}

/* BSD_SOURCE or GNU_SOURCE */
void get_strings_newway(const char *in) {
	char *cmd;
	/* one step to initilize string */
	asprintf(&cmd, "strings %s", in);

	fprintf(stdout, "%s.\n", cmd);

	/* free is necessary */
	free(cmd);
}

char *substring(char *str, char val) {
	for(;*str != val; str++) {
		if (*str == '\0') return NULL;
	}
	return str;
}

int main() {
	char val[] = "this is a string";

	/*char needle = 'b';*/
	char needle = 'a';
	char *ret = substring(val, needle);

	if (ret != NULL) {
		printf("%s\n", ret); /*pointer to the head of the string*/
		printf("%c\n", *ret);
	} else {
		printf("cannot find character %c in %s", needle, val);
	}

	char *ow = "old way";
	char *nw = "new way";
	get_strings_oldway(ow);
	get_strings_newway(nw);

	mem_leak_asprintf();
}
