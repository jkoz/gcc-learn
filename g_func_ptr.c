#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct employee_t {
	char name[31];
	char addr[123];
	int age;
	float salary;
};
typedef struct employee_t emp;

static void goodbye();
static int compare_ages(const void*, const void*);
static int compare_names(const void*, const void*);

void main() {
	emp emps[] = {
		{ "Bob", "123 ST", 45, 45000.00 },
		{ "Tony", "321 ST", 88, 46000.00 },
		{ "Mary", "hope Ave", 11, 20000.00 },
		{ "Sue", "1000 Road", 15, 90000.00 },
		{ "Fred", "12 nowhere", 99, 49000.00 }
	};
	atexit(goodbye);

	qsort(emps, 5, sizeof emps[0], compare_ages);
	printf("Sort by age\n");
	int i;
	for (i = 0; i < 5; i++) {
		printf("%-10s is aged %d\n", emps[i].name, emps[i].age);
	}

	qsort(emps, 5, sizeof emps[0], compare_names);
	printf("Sort by name\n");
	for (i = 0; i < 5; i++) {
		printf("%-10s is aged %d\n", emps[i].name, emps[i].age);
	}
}

static int compare_ages(const void* v1, const void* v2) {
	const emp *e1 = v1;
	const emp *e2 = v2;
	return e1->age - e2->age;
}

static int compare_names(const void* v1, const void* v2) {
	const emp *e1 = v1;
	const emp *e2 = v2;
	return strcmp(e1->name, e2->name);
}

static void goodbye() {
	printf("Press enter to exit: ");
	fflush(stdin);
	getchar();
}
