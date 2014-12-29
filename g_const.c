#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	int *counter1, *counter2;
} counter_s;

bool check_name(char const **in){
	return   (!strcasecmp(in[0], "Iggy") && !strcasecmp(in[1], "Pop"))
		||(!strcasecmp(in[0], "James") && !strcasecmp(in[1], "Osterberg"));
}

void check_counter(int *ctr) {
	assert(*ctr !=0);
}

/*incomming struct 'in' is marked as const*/
double ratio(counter_s const *in) {
	/* send counter2 of const struct to a func that take non-const inputs, the compiler does not complain */
	check_counter(in->counter2);
	return *in->counter1/(*in->counter2+0.0);
}

void set_elmt_const(int const *a) {
	return;
}

void set_elmt(int *a) {
	a[2] = 13;
}

void double_const() {
	/*point to non-const value*/
	int *var;

	/*point to const value*/
	int const **ptr = &var;

	int const fixed = 20;

	*ptr = &fixed;
	*var = 30;

	printf("x=%i y=%i\n", fixed, *var);

}

int main(int argc, char **argv) {
	int value[3];
	int value2 = 4;

	int *pN = &value[0];
	set_elmt_const(pN);

	/* const keyword apply immediately to type before it */

	/* p1 is a pointer to const pointer to int */
	int *const *p1;

	 /*the data pointer pointing to is const (cannot be changed)*/
	int const *pInt = &value[0];

	/* NOT OK as pInt point to a const value*/
//	set_elmt(pInt);

	/* Cast to non-const is acceptable */
	set_elmt((int*) pInt);
	/*printf("%d", pInt[2]);*/

	/* illegal */
//	*pInt = 5;

	/* OK, the pointer is not const */
	pInt = &value2;

	/* pointer itself is const (this pointer cannot be changed its value) */
	int *const pConst = &value[0];

	/* OK, data pointed is not const */
	*pConst = 5;

	/* NOT OK, the pointer is const */
//	pConst = &value2;

	/* pointer itself is const (cannot be changed) */
	int const *const pConstConst = &value[0];

	/* NOT OK, data pointed is not const*/
//	*pConstConst = 5;
	/* NOT OK, point itself is const as well<]*/
//	pConstConst = &value2;

	counter_s cc = {.counter1=malloc(sizeof(int)), .counter2=malloc(sizeof(int))};
	*cc.counter1= *cc.counter2=1;
	ratio(&cc);

	double_const();

	if (argc < 2) return 0;

	/* Need explicitly cast to `char const**` */
	char *prog = argv[0];
	char *firstArg = argv[1];
	printf("\n%s\n", prog);
	printf("%s\n", firstArg);
	return check_name((char const**) &argv[1]);
}
