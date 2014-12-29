#include <stdlib.h> //malloc
#include <strings.h> //strcasecmp
#include "entry.h"
#include "object.h"

entry *entry_new(char *key, void *value){
	entry *out = malloc(sizeof(entry));
	*out = (entry){.key = key, .value=value};
	return out;
}

def_object_copy(entry);  // expand use below delaration
/*entry *entry_copy(entry const *in){*/
	/*entry *out = malloc(sizeof(entry));*/
	/**out = *in;*/
	/*return out;*/
/*}*/

void entry_free(entry *in) {
	free(in);
}

int entry_matches(entry const *in, char const *key){
	return !strcasecmp(in->key, key);
}
