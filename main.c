#define CXCEPTIONS_NO_LOCATION
#include "cxeptions.h"

int main() {
	TRY {
		exception_t exc = EXCEPTION_NO_FMT("TestException", "test!");
		THROW(exc);
	}
	CATCH(err) {
		print_exception(err);
	}
}
