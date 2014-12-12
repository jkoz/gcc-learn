
/*gcc compilation stages:*/

/*1. preprocessing (expand macros)*/
/*$ cpp hello.c > hello.i -*/

/*2. compilation (source code -> assembly lang)*/
/*$ gcc -Wall -S hello.i*/

/*3. assembly (assembly lang -> machine code*/
/*$ as hello.s -o hello.o*/

/*4. linking (create filnal executable)*/
/*ld -dynamic-linker /lib/ld-linux-x86-64.so.2 \*/
/*/usr/lib/crt1.o \*/
/*/usr/lib/crti.o \*/
/*/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/crtbegin.o \*/
/*-L/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/ \*/
/*hello.o \*/
/*-lgcc -lgcc_eh -lc -lgcc -lgcc_eh \*/
/*/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.2/crtend.o \*/
/*/usr/lib/crtn.o \*/
/*-o hello*/

/*check linked libraries*/
/*ldd a.out*/
