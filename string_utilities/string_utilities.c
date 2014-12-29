#include <string.h>
#include "string_utilities.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h> //abort

ok_array *ok_array_new(char *instring, char const *delimiters){
	ok_array *out= malloc(sizeof(ok_array));

	/* initialize base string  */
	*out = (ok_array) { .base_string=instring };

	char *scratch = NULL;

	char *txt = strtok_r(instring, delimiters, &scratch);

	if (!txt) return NULL;

	while (txt) {
		/* re-allocate memory with new length */
		out->elements = realloc(out->elements, sizeof(char*)*++(out->length));
		out->elements[out->length-1] = txt;
		txt = strtok_r(NULL, delimiters, &scratch);
	}
	return out;
}
/* Frees the original string, because strtok_r mangled it, so it isn't useful for any other purpose. */
void ok_array_free(ok_array *ok_in){
	if (ok_in == NULL) return;
	free(ok_in->base_string);
	free(ok_in->elements);
	free(ok_in);
}

#ifdef test_ok_array
int main (){
	char *delimiters = " `~!@#$%^&*()_-+={[]}|\\;:\",<>./?\n";
	ok_array *o = ok_array_new(strdup("Hello,  reader. This is text."), delimiters);
	assert(o->length==5);
	assert(!strcmp(o->elements[1], "reader"));
	assert(!strcmp(o->elements[4], "text"));
	ok_array_free(o);
	printf("OK.\n");
}
#endif
