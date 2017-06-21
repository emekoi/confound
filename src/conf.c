#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "conf.h"
#include "util.h"

cf_Program cf_parse(char *stream) {
	// cf_Programs p;
	char *i = stream;
	while(*i) {
		printf("%c\n", *i);
		i++;
	}
}

int main(void) {
	cf_parse("hello");

  return 0;
}
