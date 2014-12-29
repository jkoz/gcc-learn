/* saving microseconds on every func call with struct as an input by defining its elements as pointers */
/* all calls within c is pass-by-value */
typedef struct entry {
   char *key;
   void *value;
} entry;

/* why dont we use struct (without pointer) ? because struct alone is a automic memory allocation */
/* new: a struct is automatically initialized when defining as 'struct Point a;' */
/* copy: any assignation with '=' will perform automatically copy of a struct  */
/* free: as an automatic memory, memory of a struct is purge once it goes out of the scope*/

/* pointer pros */
/* 1. Copying pointer is cheap (happen every func call, or return a struct) */
/* 2. Allow to modify value of the struct, (passed by ref) */
/* 3. Lots of library have subroutines with pointers */
/* 4. if a struct has pointers elements, the the convinence of plain struct
 *    goes away, we have to copy manually as well */

entry *entry_new(char *key, void *value);

entry *entry_copy(entry const *in);
void entry_free(entry *in);
int entry_matches(entry const *in, char const *key);
