#ifndef CONF_H
#define CONF_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "util.h"

typedef struct cf_Program cf_Program;

struct cf_Program {
	char *instructions;
};

// stati c char *concat(const char *str, ...);


cf_Program *cf_parse(char *stream);

#endif
