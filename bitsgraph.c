#include <stdio.h>

#define X_SIZE 32/* size of array in the X direction */
#define Y_SIZE 32/* size of the array in Y direction */
/*
 * We use X_SIZE/8 since we pack 8 bits per byte
 */
char graphics[X_SIZE / 8][Y_SIZE];   /* the graphics data */

#define SET_BIT(x,y) graphics[(x)/8][y] |= (0x80 >>((x)%8))
#define CLEAR_BIT(x,y) graphics[(x)/8][y] &= 0x00

#define PRINT_FORWARD_SLASH 0
#define PRINT_BACKSLASH 0
#define PRINT_CLEAR_MATRIX 0


/*0x80 - 1000 0000*/
/*0x40 - 0100 0000*/
/*0x20 - 0010 0000*/
/*0x10 - 0001 0000*/
/*0x08 - 0000 1000*/
/*0x04 - 0000 0100*/
/*0x02 - 0000 0010*/
/*0x01 - 0000 0001*/

int main() {
    int loc;        /* current location we are setting */

    void print_graphics(char fg, char bg, int forward); /* define void function -> print data */
	void clear_graphics(void); /* clear the matrix */
	void set_bits_backslash(void); /* set bits on backslash '\' in the matrix */
	void set_bits_slash(void); /* set bits on backslash '/' in the matrix */

	void (*func) (char, char, int); /*func is a pointer to func returning void*/
	func = print_graphics; /* func point to print_graphics */

#if PRINT_BACKSLASH
    // print backslash '\'
	set_bits_backslash();
	func('\\', ' ', 1);
#endif
#if PRINT_CLEAR_MATRIX
	// clear all bits
	clear_graphics();
	/*func('X', '.', 1);*/
#endif
#if PRINT_FORWARD_SLASH
    // print backslash /
	set_bits_slash();
	func('/', ' ', 0);
#endif
	/* int - 4 * 8 = 100000000 00000000 00000000 00000000 = 0x8000 */
	unsigned int bit, x, y, count = 0, value = 31;
	for (bit = 0x8000; bit > 0 ; bit = bit >> 1) {
		/*printf("%4x\n", bit);*/

		if ((value & bit) != 0) { /* bracket is important ( value & bit ) */
			count++;
		}
	}
	printf("%d\n", count);

    return (0);
}
/********************************************************
 * print_graphics -- print the graphics bit array       *
 *              as a set of X and .'s.                  *
 ********************************************************/
void print_graphics(char fg, char bg, int forward) {
    int x;              /* current x BYTE */
    int y;              /* current y location */
    unsigned int bit;   /* bit we are testing in the current byte, IMPORTANT this one should be unsigned */
	/* for signed value, the signed bit (1) is used for fill when performing
 	 * right shift, e.g. 1000 -> 1100*/
	/* for unsigned value, the unsigned bit (0) is used for fill when performing
 	 * right shift, e.g. 1000 -> 1100*/

    for (y = 0; y < Y_SIZE; ++y) { /*loop Y axis*/
		if (forward == 1) { /*1 : slash*/
			for (x = 0; x < X_SIZE / 8; ++x) {  /*loop X axis: char contains 8 bits, 2 loops: char loop and bit loop*/
				for (bit = 0x80; bit > 0; bit = bit >> 1) { /*bits loop*/
					if ((graphics[x][y] & bit) != 0) /* '1' & 1 = 1 : bit in matrix is turned on*/
						printf("%c", fg);
					else /* '0' & 1 = 0 : bit in matrix is turned off*/
						printf("%c", bg);
				}
			}
		} else { /* 0: backslash */
			for (x = X_SIZE / 8 - 1; x >= 0 ; --x) {  /*loop X axis: char contains 8 bits, 2 loops: char loop and bit loop*/
				for (bit = 0x80; bit > 0; bit = bit >> 1) { /*bits loop*/
					if ((graphics[x][y] & bit) != 0) /* '1' & 1 = 1 : bit in matrix is turned on*/
						printf("%c", fg);
					else /* '0' & 1 = 0 : bit in matrix is turned off*/
						printf("%c", bg);
				}
			}
        }
        printf("\n");
    }
}

void clear_graphics() {
	int loc;
    for (loc = 0; loc < X_SIZE; ++loc) { /* loop 1 -> 16 */
        CLEAR_BIT(loc, loc);
	}
}

void set_bits_backslash() {
	int loc;
    for (loc = 0; loc < X_SIZE; ++loc) { /* loop 1 -> 16 */
		SET_BIT(loc, loc); /* 10000000 -> 00000001 -> '\: backslash' */
	}
}

void set_bits_slash() {
	int loc, x, y;
    for (loc = X_SIZE - 1; loc >= 0; --loc) { /* loop 1 -> 16 */
		x = y = loc;
		graphics[(x)/8][y] |= 0x01 << (x % 8); /* 00000001 -> 1000000 -> '/: slash' */
	}
}

