#include "cxceptions.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

exception_t* cxceptions_current = NULL;
jmp_buf cxceptions_jmpbuf[CXCEPTIONS_MAX_TREE] = {0};
int cxceptions_jmpbuf_index = 0;

void cxceptions_throw_exception(exception_t* exception) {
	cxceptions_current = exception;
	if (cxceptions_jmpbuf_index <= 0) {
		cxceptions_handle_no_catch();
	} else {
		longjmp(cxceptions_jmpbuf[--cxceptions_jmpbuf_index], 0);
	}
}

void cxceptions_handle_no_catch() {
	printf("Unhandled ");
	print_exception(cxceptions_current);
	exit(-1);
}
