#include <stdio.h>
#include <gdbm.h>

/*gcc -Wall -I/usr/include/gdbm       -L/usr/lib/           dbmain.c -lgdbm -o dbmain*/
/*gcc -Wall -I/opt/gdbm-1.8.3/include -L/opt/gdbm-1.8.3/lib dbmain.c -lgdbm*/

/*env var*/
/*export C_INCLUDE_PATH=/opt/gdbm-1.8.3/include:/net/include*/
/*export LIBRARY_PATH=/opt/gdbm-1.8.3/lib:/net/lib*/

/*static library file.a*/
/*shared library file.so*/

/*force static linking with key word static*/
/*gcc -Wall -static -I/usr/include -L/usr/lib dbmain.c -lgdbm*/

/*force shared linking*/
/*gcc -I/usr/include/gdbm dbmain.c /usr/lib/libgdbm.so -o dbmain*/


int
main (void)
{
	GDBM_FILE dbf;
	datum key = { "testkey", 7 };/* key, length */
	datum value = { "testvalue", 9 }; /* value, length */
	printf ("Storing key-value pair... ");
	dbf = gdbm_open ("test", 0, GDBM_NEWDB, 0644, 0);
	gdbm_store (dbf, key, value, GDBM_INSERT);
	gdbm_close (dbf);
	printf ("done.\n");
	return 0;
}
