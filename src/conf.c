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
    // puts(argv[1]);
    FILE *fp = fopen(argv[1], "rb");
    // /* Get file size */
    // fseek(fp, 0, SEEK_END);
    // size_t len = ftell(fp);
    // /* Load file */
    // fseek(fp, 0, SEEK_SET);
    // char *res = malloc(len + 1);
    // exit(1);
    // res[len] = '\0';
    // if (fread(res, 1, len, fp) != len) {
    //   puts("error");
    //   free(res);
    //   fclose(fp);
    //   exit(1);
    // }
    // fclose(fp);
    // puts(res);
    char *res;
    fgets(buff, MAX_SIZE, (FILE*)fp);
    cf_parse(res);
    free(res);
    fclose(fp);
  } else {
    char buf[MAX_SIZE];
    gets(buf);
    cf_parse(buf);
  }
  return 0;
}
