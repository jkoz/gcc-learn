#include <stdio.h>
#include <stdlib.h>

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
