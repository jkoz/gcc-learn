#include <stdio.h>
#include <math.h> //NAN
#include <stdlib.h>

/* variadic macros */
#define loop(i, max, ...) \
	for(i = 0; i < max; i++) { \
		__VA_ARGS__ \
	}

/*loop based on NAN*/
#define loop2(ptr, ...) \
	for (ptr= items_list; !isnan(*ptr); ptr++) { \
		__VA_ARGS__ \
	}

/* for each string */
#define Foreach_string(it, ...) \
	char **it = (char*[]){__VA_ARGS__, NULL}; for (; *it; it++)

/* variadic macros and compound literal '(double []){__VA_ARGS__, NAN}' */
#define Setup_list(name, ...)                               \
	double *name ## _list = (double []){__VA_ARGS__, NAN};  \
	int name ## _len = 0;                                   \
	for (name ## _len =0;                                   \
		!isnan(name ## _list[name ## _len]);            \
	) name ## _len ++;

/*vectorizing*/
#define Fn_apply(type, fn, ...) {                                      \
	void *stopper_for_apply = (int[]){0};                              \
	type **list_for_apply = (type*[]){__VA_ARGS__, stopper_for_apply}; \
	for (; *list_for_apply != stopper_for_apply; list_for_apply++) {   \
		printf("%d\n", *((int*)*list_for_apply));                      \
		fn(*list_for_apply);                                           \
	} \
}

/*enhancing free for list of objects*/
#define Free_all(...) Fn_apply(void, free, __VA_ARGS__);


int main(){
	double *ptr, sum=0;
	Setup_list(items, 1, 2, 4, 8);
	/* loop base on last item is NAN provided by math.h */
	loop2(ptr, sum += *ptr; printf("Sum: %.2f\n", sum);)
	printf("total for items list: %g\n", sum);

#define Length(in) in ## _len
	int i;sum=0;
	Setup_list(next_set, -1, 2.2, 4.8, 0.1);
	/* loop based on length */
	loop(i, Length(next_set), sum += next_set_list[i]; printf("Sum: %.2f\n", sum);)
	printf("total for next set list: %g\n", sum);

	/* for each string */
	Foreach_string(s, "yarn", "join", "rope") { printf("%s\n", *s); }

	int *x= malloc(sizeof(x)*2); x[0]=1; x[1]=2;
	int *y= malloc(sizeof(y)*3); y[0]=3; y[1]=4;
	int *z= malloc(sizeof(z)*4); z[0]=5; z[1]=6;
	Free_all(x, y, z);

}
