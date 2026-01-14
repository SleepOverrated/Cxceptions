#include "cxeptions.h"
#include <stdio.h>

exception_t* cxceptions_current = NULL;
jmp_buf cxceptions_jmpbuf[CXEPTIONS_MAX_TREE] = {0};
int cxceptions_jmpbuf_index = 0;

void throw_exception(exception_t* exception) {
	cxceptions_current = exception;
	if (cxceptions_jmpbuf_index <= 0) {
		handle_no_catch();
	} else {
		longjmp(cxceptions_jmpbuf[--cxceptions_jmpbuf_index], 0);
	}
}

void handle_no_catch() {
	printf("Unhandled ");
	print_exception(cxceptions_current);
	exit(-1);
}

void print_exception(exception_t* e) {
	printf("%s Exception: %s\n  at %s:%lu\n", e->type, e->message, e->file, e->line);
}
