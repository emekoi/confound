#ifndef CONF_H
#define CONF_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h> 

#include "util.h"
#include "lib/fs/fs.h"

#define MAX_SIZE 0xFFFFF

typedef struct cf_Program cf_Program;

struct cf_Program {
	char *inst;
	size_t pc;
	int *mem;
};

cf_Program *cf_new_program(size_t len);
cf_Program *cf_parse_program(char *source);
void cf_run_program(cf_Program *program);

#endif
