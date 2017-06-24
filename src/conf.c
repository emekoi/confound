#include "conf.h"

static char *dirname(char *str) {
  char *p = str + strlen(str);
  while (p != str) {
    if (*p == '/' || *p == '\\') {
      *p = '\0';
      break;
    }
    p--;
  }
  return str;
}

cf_Program *cf_parse(char *source) {
	cf_Program *p = calloc(1, sizeof(cf_Program));
	p->inst = calloc(strlen(source), sizeof(char));
	char *i = source;
  int k = 0;
	while (*i) {
		switch (*i) {
			case '>':case '<':
			case '+':case '-':
			case '.':case ',':
			case '[':case ']': {
				// printf("%c\n", *i);
				p->inst[k++] = *i;
				break;
			} default:
				break;
		}
		i++;
	}
	printf("%s\n", p->inst);
	return p;
}

int main(int argc, char **argv) {
  if (argc > 1) {

    char buf[1024];
    size_t size = sizeof(buf);
    ASSERT( getcwd(buf, size) != NULL );
    dirname(buf);    
    puts(buf);

  } else {
    char buf[MAX_SIZE];
    gets(buf);
    cf_parse(buf);
  }
  return 0;
}
