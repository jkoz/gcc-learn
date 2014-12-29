#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define Peval(cmd) printf(#cmd ": %d\n", cmd)
typedef struct point {
	double x, y;
} point;

typedef struct {
	/* anonymous elements of structure threepoint */
	/* compile with gcc -fms-extensions -lm */
	union {
		struct point;
		point p2;
	};
	double z;
} threepoint;

double length (point p){
	return sqrt(p.x*p.x + p.y*p.y);
}

double threelength (threepoint p){
	return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
}

/*emmbedded programming*/
union {
	/*32-bit value*/
	int whole;
	/*or four 8-bits bytes*/
	struct {char c0, c1, c2, c3; } byte;
} value;

/*pseuodo-polymorphism*/
enum Type { INTS, FLOATS, DOUBLE };
struct S {
	enum Type s_type;
	union {
		int s_ints[2];
		float s_floats[2];
		double s_double;
	};
};

typedef struct {
	double pressure, moles, temp;
} ideal_struct;

/* set default values for struct */
/*if an item is defined multiple times, then the last initialization takes precedence*/

/** Find the volume (in cubic meters) via the ideal gas law: V =nRT/P
 * Inputs:
 * pressure in atmospheres (default 1)
 * moles of material (default 1)
 * temperature in Kelvins (default freezing = 273.15)
 *   */
#define ideal_pressure(...) ideal_pressure_base((ideal_struct){.pressure=1, .moles=1, .temp=273.15, __VA_ARGS__})

static double ideal_pressure_base(ideal_struct in) {
	return 8.314 * in.moles*in.temp/in.pressure;
}

typedef struct {
	double width, height;
} size_s;

static size_s width_height(char *papertype){
	return !strcasecmp(papertype, "A4") ? (size_s) {.width=210, .height=297}
		 : !strcasecmp(papertype, "Letter") ? (size_s) {.width=216, .height=279}
		 : !strcasecmp(papertype, "Legal")  ? (size_s) {.width=216, .height=356}
		 : (size_s) {.width=NAN, .height=NAN};
}

static void struct_packed() {
	struct gif_hdr
	{                      /* expect */
		char signature[3]; /* offset=0  bytes=3 data_bytes=(0, 1, 2)*/
		char version[3];   /* offset=3  bytes=3 data_bytes=(3, 4, 5)*/
		int width;         /* offset=6  bytes=4 data_bytes=(6, 7, 8, 9)*/
		int height;        /* offset=10 bytes=4 */
		char colormap;     /* offset=14 bytes=1 */
		char bgcolor;      /* offset=15 bytes=1 */
		char ratio;        /* offset=16 bytes=1 */
		                   /*     total bytes=17 */
	} __attribute__((__packed__)) ;
	struct gif_hdr *dsptr;
	printf("Size of structure data = %d\n", sizeof(struct gif_hdr));
	dsptr = (struct gif_hdr*)malloc(sizeof(struct gif_hdr));
	printf("Offset of signature = %d\n", &(dsptr->signature[0]) - &(dsptr->signature[0]) );
	printf("Offset of version = %d\n", &(dsptr->version[0]) - &(dsptr->signature[0]) );
	printf("Offset of width = %d\n", (char*)&(dsptr->width) - &(dsptr->signature[0]));
	printf("Offset of height = %d\n", (char*)&(dsptr->height) - &(dsptr->signature[0]));
	printf("Offset of colormap = %d\n", &(dsptr->colormap) - &(dsptr->signature[0]));
	printf("Offset of bgcolor = %d\n",&(dsptr->bgcolor) - &(dsptr->signature[0]));
	printf("Offset of ratio = %d\n", &(dsptr->ratio) - &(dsptr->signature[0]));
}

static void struct_no_packed() {
	struct gif_hdr
	{                      /* expect */
		char signature[3]; /* offset=0  bytes=3 data_bytes=(0, 1, 2)*/
		char version[3];   /* offset=3  bytes=3 data_bytes=(3, 4, 5)*/
		int width;         /* offset=6  bytes=4 data_bytes=(6, 7, 8, 9)*/
		int height;        /* offset=10 bytes=4 */
		char colormap;     /* offset=14 bytes=1 */
		char bgcolor;      /* offset=15 bytes=1 */
		char ratio;        /* offset=16 bytes=1 */
		                   /*     total bytes=17 */
	};
	struct gif_hdr *dsptr;
	printf("Size of structure data = %d\n", sizeof(struct gif_hdr));
	dsptr = (struct gif_hdr*)malloc(sizeof(struct gif_hdr));
	printf("Offset of signature = %d\n", &(dsptr->signature[0]) - &(dsptr->signature[0]) );
	printf("Offset of version = %d\n", &(dsptr->version[0]) - &(dsptr->signature[0]) );
	printf("Offset of width = %d\n", (char*)&(dsptr->width) - &(dsptr->signature[0]));
	printf("Offset of height = %d\n", (char*)&(dsptr->height) - &(dsptr->signature[0]));
	printf("Offset of colormap = %d\n", &(dsptr->colormap) - &(dsptr->signature[0]));
	printf("Offset of bgcolor = %d\n",&(dsptr->bgcolor) - &(dsptr->signature[0]));
	printf("Offset of ratio = %d\n", &(dsptr->ratio) - &(dsptr->signature[0]));
}

static void struct_compound_litterals() {
	size_s a4size = width_height("a4");
	printf("width= %g, height=%g\n", a4size.width, a4size.height);

	printf("volume given defaults: %g\n", ideal_pressure() );
	printf("volume given boiling temp: %g\n", ideal_pressure(.temp=373.15) );
	printf("volume given two moles: %g\n", ideal_pressure(.moles=2) );
	printf("volume given two boiling moles: %g\n", ideal_pressure(.moles=2, .temp=373.15) );
}

static void struct_fm_extension() {
	threepoint p = {.x=3, .y=0, .z=4};
	printf("p is %g units from the origin\n", threelength(p));
    double xylength = length(p.p2);
	printf("Its projection onto the XY plane is %g units from the origin\n", xylength);
}

void structs_are_copied() {
	typedef struct point {
		int x, y;
		char *c;
	} point;
	char c = 32;
	point p = (point) {.x=5, .y=7, .c = &c };
	point p2 = p; /* p2 is a copied of p, IMPORTANT: c is a pointer, so only its address is copied, but value*/

	p.x = 6;
	p.y = 9;
	Peval(p.x);
	Peval(p.y);
	Peval(p.c);
	Peval(*p.c);
	Peval(p2.x);
	Peval(p2.y);
	Peval(p2.c);
	Peval(*p2.c);


	point structs_are_copied_inner(point p) {
		printf("address of cloned param in func p = %p\n", &p);
		/* p is copied when passing to this func */
		p.x = 99;
		p.y = 99;
		char k = 44;
		p.c = &k; /* DONT DO THIS, as k is going to be delete after current scope */

		return p; /* OK, new point is created and returned to caller */
	}

	printf("address of local var in caller p = %p\n", &p);
	point kk = structs_are_copied_inner(p);
	printf("address of local var in caller kk = %p\n", &kk);

	Peval(kk.x);
	Peval(kk.y);
	Peval(*kk.c);

	int normal_var(int x) {
		/* x is copied from the caller */
		printf("address of param var in caller x = %p\n", &x);
		x = 9;
		return x; /* x is copied and return to caller */
	}

	int x = 11;
	printf("address of local var in caller x = %p\n", &x);
	int ik = normal_var(x);
	printf("address of return var in caller ik = %p\n", &ik);
}

struct node {
	int data;
};

void incorrect_addnode(struct node* n1) {
	/** IMPORTANT: n1 is just a copied of caller pointer!
	 * n1 is going to be free after this scope
	 * Thus, assign new memory for n1 is a memory leak, as
	 * we don't have reference to this new memory after returning to
	 * the caller */
	printf("address of cloned pointer in func (will be deleted after this call): %p\n", &n1);
	n1 = (struct node*)malloc(sizeof(struct node));
	n1->data = 9;
}


void struct_common_mistake(void)
{
	struct node* n1 = NULL;
	printf("address of pointer n1: %p\n", &n1);
	incorrect_addnode(n1);
	if (n1 == NULL) {
		printf("n1 is still pointing to NULL");
	}
}

void correct_addnode(struct node **n1) {
	printf("address of pointer (*n1): %p\n", &(*n1));
	*n1 = (struct node*)malloc(sizeof(struct node));
	(*n1)->data = 9;
}

void struct_fix_common_mistake(void)
{
	struct node* n1 = NULL;
	printf("address of pointer n1: %p\n", &n1);
	correct_addnode(&n1);
	Peval(n1->data);

}

struct signature { char sign; char version; };
struct id { char id; char platform; };
struct data { struct signature sig; struct id idv; char data[100]; };

struct signature *extractsignature(struct data* d) {
	struct signature* sig = (struct signature*)d;
	printf("address of local var: sig = %p\n", &sig);
	return sig;
}

struct signature *test_return_struct_pointer_inner() {
	struct signature *kkk;
	printf("address of local var: kkk = %p\n", &kkk);
	return kkk;
}

struct signature *test_return_struct_pointer_inner2() {
	struct signature *kkk2 = malloc(sizeof(struct signature));
	printf("address of local var: kkk2 = %p\n", &kkk2);
	return kkk2;
}

void test_return_struct_pointer() {
	printf("if pointer in inner func is pointing to NULL (uninitialized), then\ncompiler destroy the local pointer memoery in the inner func\n");
	struct signature *kkk = test_return_struct_pointer_inner();
	printf("address of local kkk in caller: kkk = %p\n", &kkk);

 	 printf("\nif pointer in inner func is pointing to a valid heap memory, then it\nkeep its address and return to caller\n");
	struct signature *kkk2 = test_return_struct_pointer_inner2();
	printf("address of local kkk2 in caller: kkk2 = %p\n", &kkk2);
}

struct id* extractid( struct data* d) {
	struct id* idv = (struct id*)d;
	return idv;
}

void casting_struct() {
	struct data* img;
	img = malloc(sizeof(struct data));
	img->sig.sign = 11;
	img->sig.version = 2;
	img->idv.id = 22;
	img->idv.platform = 33;
	struct signature* sign = extractsignature(img);
	printf("address of return var: sig = %p\n", &sign);
	printf("sign=%d, version=%d\n", sign->sign, sign->version);

	/*struct id* idval = extractid(img);*/

	free(img);
}

int main(){
//	struct_no_packed(); // it's packed now
//	struct_packed();
//	structs_are_copied();
//	struct_common_mistake();
//	struct_fix_common_mistake();
//	casting_struct();
	test_return_struct_pointer();
}

