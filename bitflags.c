/*-*/
/********************************************************
 * Question:						*
 * 	The flag HIGH_SPEED works.			*
 * 	The flag DIRECT_CONNECT does not.		*
 *	Why?						*
 ********************************************************/
/*+*/
#include <stdio.h>
                             /*Position Binary    Hexadecimal*/
const int HIGH_SPEED     = (1<<0);   /* 00000001  0x01            modem is running fast */
const int DIRECT_CONNECT = (1<<1);   /* 00000010  0x02            we are using a hardwired connection */
const int FRAMING_ERROR  = (1<<2);   /* 00000100  0x02            we are using a hardwired connection */

char flags = 0;         /* start with nothing */

/*second solution packed structure*/
struct char_and_status {
	char character;
	int high_speed:1; /* use only 1 bit in integer */
	int direct_connect:1; /* use only 1 bit in integer */
	int framming_error:1; /* use only 1 bit in integer */
};

int main()
{
	/*All flags are unset*/
    /*0000 0000*/
    /*0000 0001*/
    /*AND------*/
    /*0000 0000*/
    /*So, last bit is zero */
    if ((flags & HIGH_SPEED) == 0)
        printf("High speed does NOT set\n");

    if ((flags & DIRECT_CONNECT) == 0)
        printf("Direct connect does NOT set\n");

	/*high speed flag is set*/
    flags |= HIGH_SPEED;
    if ((flags & HIGH_SPEED) != 0)
        printf("High speed set\n");

	/*direct connect flag is set*/
    flags |= DIRECT_CONNECT;
    if ((flags & DIRECT_CONNECT) != 0)
        printf("Direct connect set\n");

	/*unset direct connect flag*/
	flags &= ~DIRECT_CONNECT;
    if ((flags & DIRECT_CONNECT) == 0)
        printf("Direct connect was unset\n");

    return (0);
}
