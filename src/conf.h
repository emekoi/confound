#ifndef CONF_H
#define CONF_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "util.h"

#define MAX_SIZE 0xFFFFF

typedef struct cf_Program cf_Program;

struct cf_Program {
	char *inst;
};

// stati c char *concat(const char *str, ...);


cf_Program *cf_parse(char *source);

#endif
