#include "cxeptions.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

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

exception_t fmt_exception(char* type, char* format, ...) {
	exception_t exception = {0};
	va_list args;
	va_start(args, format);

	char buf[CXEPTIONS_MESSAGE_BUF];
	vsnprintf(buf, sizeof buf, format, args);
	va_end(args);

	exception.type = type;
	char* dest = malloc(strlen(buf) + 1);
	exception.message = strcpy(dest, buf);
	return exception;
}

void handle_no_catch() {
	printf("Unhandled ");
	print_exception(cxceptions_current);
	exit(-1);
}

void print_exception(exception_t* e) {
	printf("%s Exception: %s\n  at %s:%lu\n", e->type, e->message, e->file, e->line);
}
