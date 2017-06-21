#include "conf.h"

static char *concat(const char *str, ...) {
  va_list args;
  const char *s;
  /* Get len */
  int len = strlen(str);
  va_start(args, str);
  while ((s = va_arg(args, char*))) {
    len += strlen(s);
  }
  va_end(args);
  /* Build string */
  char *res = malloc(len + 1);
  if (!res) return NULL;
  strcpy(res, str);
  va_start(args, str);
  while ((s = va_arg(args, char*))) {
    strcat(res, s);
  }
  va_end(args);
  return res;
}

char* stradd(const char* a, char b){
    size_t len = strlen(a) + strlen(&b);
    char *ret = (char*)malloc(len * sizeof(char) + 1);
    *ret = '\0';
    return strcat(strcat(ret, a), &b);
}


cf_Program *cf_parse(char *stream) {
	cf_Program *p = calloc(1, sizeof(cf_Program));
	p->instructions = calloc(strlen(stream), sizeof(char))
	char *i = stream;
	while (*i) {
		switch (*i) {
			case '>':case '<':
			case '+':case '-':
			case '.':case ',':
			case '[':case ']': {
				printf("%s\n", stradd(p->instructions, *i));
				p->instructions = stradd(p->instructions, *i);
				break;
			} default:
				break;
		}
		i++;
	}
	// printf("%s\n", p->instructions);
	return p;
}

int main(void) {
	cf_parse("[+-->]");

  return 0;
}
