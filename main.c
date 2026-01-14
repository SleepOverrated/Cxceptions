#include "cxeptions.h"
#include <stdio.h>

void some_func() {
	printf("SOME FUNC WOOOOHOOOO!\n");
}

int main(void) {

	THROW("TEST!", "jaja");

	return 0;
}
