#ifndef CONF_H
#define CONF_H

typedef struct cf_Program cf_Program;

struct cf_Program {
	char *instructions;
};

cf_Program cf_parse(char *stream);

#endif
