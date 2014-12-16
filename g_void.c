#include <stdlib.h>
#include <memory.h>

void *memdup(void *mem, int size) {
	void *ptr;
	ptr = malloc(size);
	memcpy(ptr, mem, size);
	return ptr;
}

void main() {
	float f_arr[] = { 1.2, 2.3, 3.4, 4.5 };
	int i_arr[] = { 1, 2, 3, 4, 5 };
	char c_arr[] = "helloworld\n";

	float *f_arr2;
	int *i_arr2;
	char *c_arr2;

	f_arr2 = memdup(f_arr, sizeof f_arr);
	i_arr2 = memdup(i_arr, sizeof i_arr);
	c_arr2 = memdup(c_arr, sizeof c_arr);

	free(f_arr2);
	free(i_arr2);
	free(c_arr2);
}
