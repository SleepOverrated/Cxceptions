#ifndef CXEPTIONS_H
#define CXEPTIONS_H

#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef CXCEPTIONS_MESSAGE_BUF
#define CXCEPTIONS_MESSAGE_BUF 1024
#endif // !CXCEPTIONS_MESSAGE_BUF

#ifndef CXCEPTIONS_MAX_TREE
#define CXCEPTIONS_MAX_TREE 255
#endif // !CXCEPTIONS_MAX_TREE

typedef struct exception {
	char* type;
	char* message;

#ifndef CXCEPTIONS_NO_LOCATION // Allow to remove location information
	char* file;
	size_t line;
#endif // !CXCEPTIONS_NO_LOCATION

} exception_t;

extern exception_t* cxceptions_current;
extern jmp_buf cxceptions_jmpbuf[CXCEPTIONS_MAX_TREE];
extern int cxceptions_jmpbuf_index;

void cxceptions_throw_exception(exception_t* exception);
void cxceptions_handle_no_catch();

// Allow to remove location information
#ifdef CXCEPTIONS_NO_LOCATION
static inline void print_exception(exception_t* e) {
	fprintf(stderr, "%s Exception: %s\n", e->type, e->message);
}
#else
static inline void print_exception(exception_t* e) {
	fprintf(stderr, "%s Exception: %s\n  at %s:%lu\n", e->type, e->message, e->file, e->line);
}
#endif

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define TRY                                               \
	setjmp(cxceptions_jmpbuf[cxceptions_jmpbuf_index++]); \
	char CONCAT(cxceptions_check, __LINE__) = 0;          \
	for (; CONCAT(cxceptions_check, __LINE__) == 0 && cxceptions_current == NULL; cxceptions_jmpbuf_index--, CONCAT(cxceptions_check, __LINE__) = 1)

#define CATCH(var_name)                          \
	char CONCAT(cxceptions_catch, __LINE__) = 0; \
	for (exception_t* var_name = cxceptions_current; CONCAT(cxceptions_catch, __LINE__) == 0 && cxceptions_current != NULL; CONCAT(cxceptions_catch, __LINE__) = 1)

#define EXCEPTION(t, m) \
	(exception_t) { .type = t, .message = m }

// Allow to remove location information
#ifdef CXCEPTIONS_NO_LOCATION

#define THROW(exception) cxceptions_throw_exception(&exception)

#else

#define THROW(exception)                             \
	exception_t CONCAT(throw, __LINE__) = exception; \
	CONCAT(throw, __LINE__).line = __LINE__;         \
	CONCAT(throw, __LINE__).file = __FILE__;         \
	cxceptions_throw_exception(&CONCAT(throw, __LINE__))

#endif // !CXCEPTIONS_NO_LOCATION

#endif // !CXEPTIONS_H
