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
	char *name;
	char *mem;
	size_t len;
	size_t ic;
	size_t dp;
};

cf_Program *cf_new_program(char *name, size_t len);
void cf_close_program(cf_Program *program);
cf_Program *cf_parse_program(char *name, char *source);
size_t *cf_compute_jumptable(cf_Program *program);
void cf_run_program(cf_Program *program);

#endif
