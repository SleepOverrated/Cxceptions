#ifndef CXEPTIONS
#define CXEPTIONS

#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef CXCEPTIONS_MESSAGE_BUF
#define CXCEPTIONS_MESSAGE_BUF 1024
#endif // !CXEPTIONS_MESSAGE_BUF

#ifndef CXCEPTIONS_MAX_TREE
#define CXCEPTIONS_MAX_TREE 255
#endif /* ifndef CXEPTIONS_MAX_TREE */

typedef struct exception {
	char* type;
	char* message;

	char* file;
	size_t line;
} exception_t;

extern exception_t* cxceptions_current;
extern jmp_buf cxceptions_jmpbuf[CXCEPTIONS_MAX_TREE];
extern char has_catch[];
extern int cxceptions_jmpbuf_index;

void cxceptions_throw_exception(exception_t* exception);
exception_t cxceptions_fmt_exception(char* type, char* format, ...);
void cxceptions_handle_no_catch();
void print_exception(exception_t* exception);

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define TRY                                               \
	setjmp(cxceptions_jmpbuf[cxceptions_jmpbuf_index++]); \
	char CONCAT(cxceptions_check, __LINE__) = 0;          \
	for (; CONCAT(cxceptions_check, __LINE__) == 0 && cxceptions_current == NULL; cxceptions_jmpbuf_index--, CONCAT(cxceptions_check, __LINE__) = 1)

#define CATCH(var_name)                          \
	char CONCAT(cxceptions_catch, __LINE__) = 0; \
	for (exception_t* var_name = cxceptions_current; CONCAT(cxceptions_catch, __LINE__) == 0 && cxceptions_current != NULL; CONCAT(cxceptions_catch, __LINE__) = 1, free(var_name->message))

#define EXCEPTION(t, m, ...) cxceptions_fmt_exception(t, m, ##__VA_ARGS__)

#define EXCEPTION_NO_FMT(t, m) \
	(exception_t) { .type = t, .message = m }

#define THROW(exception)                             \
	exception_t CONCAT(throw, __LINE__) = exception; \
	CONCAT(throw, __LINE__).line = __LINE__;         \
	CONCAT(throw, __LINE__).file = __FILE__;         \
	throw_exception(&CONCAT(throw, __LINE__))

#endif // !CXEPTIONS
