#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

double ideal_pressure_base(ideal_struct in) {
	return 8.314 * in.moles*in.temp/in.pressure;
}

typedef struct {
	double width, height;
} size_s;

size_s width_height(char *papertype){
	return !strcasecmp(papertype, "A4") ? (size_s) {.width=210, .height=297}
		 : !strcasecmp(papertype, "Letter") ? (size_s) {.width=216, .height=279}
		 : !strcasecmp(papertype, "Legal")  ? (size_s) {.width=216, .height=356}
		 : (size_s) {.width=NAN, .height=NAN};
}

int main(){
	size_s a4size = width_height("a4");
	printf("width= %g, height=%g\n", a4size.width, a4size.height);

	printf("volume given defaults: %g\n", ideal_pressure() );
	printf("volume given boiling temp: %g\n", ideal_pressure(.temp=373.15) );
	printf("volume given two moles: %g\n", ideal_pressure(.moles=2) );
	printf("volume given two boiling moles: %g\n", ideal_pressure(.moles=2, .temp=373.15) );

	threepoint p = {.x=3, .y=0, .z=4};
	printf("p is %g units from the origin\n", threelength(p));
    double xylength = length(p.p2);
	printf("Its projection onto the XY plane is %g units from the origin\n", xylength);
}

