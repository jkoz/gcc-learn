#define _GNU_SOURCE //cause stdio.h to include vasprintf
#include <stdio.h>  //printf, vasprintf
#include <stdarg.h> //va_start, va_end
#include <stdlib.h> //system, free
#include <assert.h>

#define System_w_printf(outval, ...) {          \
	    char *string_for_systemf;                   \
	    asprintf(&string_for_systemf, __VA_ARGS__); \
	    outval = system(string_for_systemf);        \
	    free(string_for_systemf);                   \
	}

int system_w_printf(char const *fmt, ...) __attribute__ ((format (printf,1,2)));

int system_w_printf(char const *fmt, ...){
	char *cmd;
	va_list argp;
	va_start(argp, fmt);
	vasprintf(&cmd, fmt, argp);
	va_end(argp);
	int out= system(cmd);
	free(cmd);
	return out;
}
int main(int argc, char **argv){
	assert(argc == 2);

	int out;
	System_w_printf(out, "ls %s", argv[1]);

	system_w_printf("ls %s", argv[1]);

	return out;
}
