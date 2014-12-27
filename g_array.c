#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define RETURN_STRING_LITTERAL 0
#define RETURN_GLOBAL_ARRAY 0
#define RETURN_STATIC_STRING 0
#define RETURN_DYNAMIC_STRING 0
// the best solution
#define RETURN_PREALLOCATED_STRING 0
#define RETURN_STRUCT_ARRAY 0
#define DEMONTRATION_ARRAY 0
#define MATRIX 1

// EXAMPLE OF INCORRECT IMPLEMENTATION OF RETURNING A STRING
/*int *return_int_arr() {*/
	/*int arr[] = {1, 2, 3}; // allocate in a stack , local variable, can not return*/
	/*return arr; // return a local variable*/
/*}*/

/*int main() {*/
	/*int a[10];*/
	/*a = return_int_arr(); // can not assign to array lvalue, rvalue*/
	/*return 0;*/
/*}*/

/*SOLUTION 1: only string array, read only cant modify*/
char *func_1() {
	return "string litteral";
}

/*SOLUTION 2: everybody can modify the global array, waste of mem, and override in next call*/
char global_arr[SIZE];
char *func_2() {
	strncpy(global_arr, "Global array", SIZE);
	return global_arr;
}

/*SOLUTION 3: overwritten on next call and waste of mem*/
char *func_3() {
	static char st_arr[] = "static string"; // stored in data segment of the process
	return st_arr;
}

/*SOLUTION 4: could forget to free object -> memory leak*/
char *func_4() {
	char *buf = malloc(SIZE); // stored in head
	strncpy(buf, "dynamic string", SIZE);
	return buf;
}
/*BEST SOLUTION 5:caller manage memory itselft */
int func_5(char *result, int size) {
	strncpy(result, "Preallocated string", size);
	return 0; // return status error
}

/*SOLUTION 6: use struct*/
struct Data {
	char buf[100];
};
struct Data func_6() {
	struct Data d; // store in stack
	strncpy(d.buf, "struct store an array of string", 100);
	return d;
}
/*which similar to */
int returnInt() {
	int a = 1; // store in stack
	return a;
}

int main() {
#if RETURN_STRING_LITTERAL
	printf("%s", func_1());
#elif RETURN_GLOBAL_ARRAY
	printf("%s", func_2());
#elif RETURN_STATIC_STRING
	printf("%s", func_3());
#elif RETURN_DYNAMIC_STRING
	char *s = func_4();
	printf("%s", s);
	if (s) free(s);
#elif RETURN_PREALLOCATED_STRING
	char *buf;
	buf = malloc(SIZE);
	if (buf) {
		func_5(buf, SIZE);
		printf("%s", buf);
		free(buf);
	}
#elif RETURN_STRUCT_ARRAY
	struct Data d = func_6();
	printf("%s", d.buf);
#elif DEMONTRATION_ARRAY
	int index ;
#define ARRAY_SIZE 10
	char array[ARRAY_SIZE + 1] = "0123456789";
	printf("&array[index] (array+index) array[index](char value) array[index](hex value)\n");
	for(index = 0; index < ARRAY_SIZE; ++index)
		printf("%-10p %-10p %c 0x%x\n", &array[index], (array+index), array[index], array[index]);
#elif MATRIX
	int m[60][32];

	// fast
	/*register int *ptr;*/
	/*for(ptr = &m[0][0]; ptr <= &m[60 - 1][32 -1]; ptr++) *ptr = -1;*/
	
	// library subroutine memset
	memset(m, 1, sizeof(m));

	// slow
	int x, y;
	for(x = 0; x < 32; x++) {
		for(y = 0; y < 60; y++) {
			printf("%d", m[x][y]);
		}
		printf("\n");
	}
#endif

}
