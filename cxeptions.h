#ifndef CXEPTIONS
#define CXEPTIONS

#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef CXEPTIONS_MESSAGE_BUF
#define CXEPTIONS_MESSAGE_BUF 1024
#endif // !CXEPTIONS_MESSAGE_BUF

#ifndef CXEPTIONS_MAX_TREE
#define CXEPTIONS_MAX_TREE 255
#endif /* ifndef CXEPTIONS_MAX_TREE */

typedef struct exception {
	char* type;
	char* message;

	char* file;
	size_t line;
} exception_t;

extern exception_t* cxceptions_current;
extern jmp_buf cxceptions_jmpbuf[CXEPTIONS_MAX_TREE];
extern char has_catch[];
extern int cxceptions_jmpbuf_index;

void throw_exception(exception_t* exception);
void handle_no_catch();
void print_exception(exception_t* exception);

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

#define TRY                                               \
	setjmp(cxceptions_jmpbuf[cxceptions_jmpbuf_index++]); \
	for (char CONCAT(cxceptions_check, __LINE__) = 0; CONCAT(cxceptions_check, __LINE__) == 0 && cxceptions_current == NULL; cxceptions_jmpbuf_index--, CONCAT(cxceptions_check, __LINE__) = 1)

#define CATCH(var_name)                         \
	exception_t* var_name = cxceptions_current; \
	if (cxceptions_current != NULL)

#define THROW(t, m, ...)                                  \
	char CONCAT(strbuf, __LINE__)[CXEPTIONS_MESSAGE_BUF]; \
	sprintf(CONCAT(strbuf, __LINE__), m, ##__VA_ARGS__);  \
	THROW_NO_FMT(t, CONCAT(strbuf, __LINE__));

#define THROW_NO_FMT(t, m)                     \
	exception_t CONCAT(throw, __LINE__) = {0}; \
	CONCAT(throw, __LINE__).type = t;          \
	CONCAT(throw, __LINE__).message = m;       \
	CONCAT(throw, __LINE__).line = __LINE__;   \
	CONCAT(throw, __LINE__).file = __FILE__;   \
	throw_exception(&CONCAT(throw, __LINE__));

#define THROW_EX(exception) throw_exception(&exception);
#endif // !CXEPTIONS
