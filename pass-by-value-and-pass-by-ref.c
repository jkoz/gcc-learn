#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Peval(cmd) printf(#cmd ": %d\n", cmd)
 
struct data
{
	int x;
	int y;
};

/* pass by value */
int called_function_values(int, int);
void calling_function_values(void);
struct data called_function_values_struct(struct data);
void calling_function_values_struct(void);

/* pass by reference */
int* called_function_ref(int* x);
void calling_function_ref(void);
struct data* called_function_ref_struct(struct data *);
void calling_function_ref_struct(void);

int main() {
    /*calling_function_ref();*/
	/*calling_function_values();*/
	/*calling_function_values_struct();*/
	calling_function_ref_struct();

	return 0;
}

int called_function_values(int x, int y) {
	int t1, t2, t3;
	t1 = x;
	t2 = y;
	t3 = t1 + t2;
	return t3;
}

void calling_function_values(void) {
	int t1, t2, t3;
	t1 = 10;
	t2 = 20;

	/* only the values (x, y) is passed to the called func*/
	/* after the values passed, these values are copied onto the respective stack of the called func*/
	t3 = called_function_values(t1, t2);
}

void calling_function_ref(void) {
	int t1, *t2;
	t1 = 10;
	t2 = called_function_ref(&t1);
	printf("t2=%d\n", *t2); /* 20 */
	free(t2);
}

int* called_function_ref(int* x) {
	int t2;
	int *t1;
	int *t3;
	t1 = x;
	t2 = 10;

	/*calulate*/
	int tmp = *t1 + t2;

	/*copy value to heap memory*/
	t3 = malloc(sizeof(int));
	memcpy(t3, &tmp, sizeof(int));

	return t3; // this will copy address stored in pointer t3 return to calling (freeable)
}

void calling_function_values_struct(void) {
	struct data var;
	var.x = 10;
	var.y = 20;
	struct data badreturn = called_function_values_struct(var);
	Peval(badreturn.x); // return correct values, but as struct are copied when returning (overhead)
	Peval(badreturn.y);
	Peval(var.x); //value remain unchange because called_function_values_struct only modify copy of var
	Peval(var.y);
}

struct data called_function_values_struct(struct data d) {
	d.x++; /* modify on copied only */
	d.y++; /* modify on copied only */
	return d; /* create 2nd copied of param d, and return to caller */
}

void calling_function_ref_struct(void) {
	struct data var;
	var.x = 10;
	var.y = 20;
	struct data *ret= called_function_ref_struct(&var);
	/* only copy of 4/8 bits address, hence speed up */
	Peval(ret->x); // value is updated
	Peval(ret->y);
	Peval(var.x); // value is updated
	Peval(var.y);
}
struct data* called_function_ref_struct(struct data *d) {
	d->x++;
	d->y++;
	return d;
}
