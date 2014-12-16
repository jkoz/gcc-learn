#include <stdlib.h>
#include <stdio.h>

// 1. Basic type: char, short, etc

// 2. Derived types:
// * pointer to
// [] array of
// () function returning

// 3. grouping parenthese (())
// 4. identifiers

// Rules: grouping parenthese -> posfix operatiors []() -> prefix operators
//  1. start with variable name (leftmost identifier)
//  2. Go right if possible and left if compusory:
//                              - hit a closing parentheis
//                              - after a "function returning.."
//                              - reach the end of the declaration
//  3. end with the basic type
//  NOTES: if a const and/or volatile is next to a basic type, the keyword applies to that basic type.
//         else the keyword applies to the pointer on its immediate left.

// foo1 is 'an array' of seven pointer to pointer to long
long **foo1[7];

// foo2 is 'an array' of an array of 8 pointers to pointer to pointer to function
// returning a pointer to an array of pointer to char
char *(*(**foo2[][8])())[];

// foo3 is 'a pointer' to a function returning a pointer to a const pointer to char
char *const *(*foo3)();

// foo4 (leftmost) is 'an array' of 10 pointers to function(int**) returning a pointer to char
char *(*foo4[10])(int **p);

// func is 'a pointer' to a function, taking int as arg, returning void
void (*func)(int);

// ptr_to_func is a synonym for a pointer to a function, taking int as arg, returning void
typedef void (*ptr_to_func) (int);

// signal is 'a function' returning a pointer to a function, taking int as arg, return void
void (*signal(int sig, void (*func)(int))) (int);
// which is similar to
ptr_to_func signal(int sig, ptr_to_func);

