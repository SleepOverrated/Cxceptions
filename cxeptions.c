#include "cxeptions.h"
#include <stdarg.h>
#include <stdio.h>
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

exception_t cxceptions_fmt_exception(char* type, char* format, ...) {
	exception_t exception = {0};
	va_list args;
	va_start(args, format);

	char buf[CXCEPTIONS_MESSAGE_BUF];
	vsnprintf(buf, sizeof buf, format, args);
	va_end(args);

	exception.type = type;
	char dest[strlen(buf) + 1];
	exception.message = strcpy(dest, buf);
	return exception;
}

void cxceptions_handle_no_catch() {
	printf("Unhandled ");
	print_exception(cxceptions_current);
	exit(-1);
}
