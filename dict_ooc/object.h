/** Copy a key/value pair. The new entry has 2 new pointers pointing to
* the values in the old pair, not copies of their data. This is shallow
* copy  */
#define def_object_copy(tname, ...)         \
	tname *tname## _copy(tname const *in) { \
		tname *out = malloc(sizeof(tname)); \
		*out = *in;                         \
		__VA_ARGS__;                        \
		return out;                         \
	}
