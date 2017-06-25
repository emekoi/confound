#include "conf.h"

static char *dirname(char *str) {
  char *dir = calloc(strlen(str), sizeof(char));
  strcpy(dir, str);
  char *p = dir + strlen(dir);
  while (p != str) {
    if (*p == '/' || *p == '\\') {
      *p = '\0';
      break;
    }
    p--;
  }
  return dir;
}

static char *basename(char *str) {
  char *p = str + strlen(str);
  char *file = "";
  while (p != str) {
    if (*p == '/' || *p == '\\') {
      UNUSED(*p++);
      file = p;
      break;
    }
    p--;
  }
  return file;
}

char *strip(char *s) {
    size_t size;
    char *end;

    size = strlen(s);

    if (!size)
        return s;

    end = s + size - 1;
    while (end >= s && isspace(*end))
        end--;
    *(end + 1) = '\0';

    while (*s && isspace(*s))
        s++;

    return s;
}

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
				p->inst[k++] = *i;
				break;
			} default:
				break;
		}
		i++;
	}
  p->inst[k+1] = '\0';
	return p;
}

int main(int argc, char **argv) {
  clock_t start, end, cpu;
  start = clock();
  if (argc > 1) {
    char *path = dirname(concat("./", strip(argv[1]), NULL));
    char *file = basename(concat("./", strip(argv[1]), NULL));
    printf("\npath : %s\n", path);
    printf("file : %s\n", file);

    fs_error(fs_mount(path));
    fs_error(fs_setWritePath(path));
    /* check that file exists */
    if (fs_exists(file)) {
      /* read the file */
      size_t len;
      char *data = fs_read(file, &len);
      /* parse file*/
      cf_parse(data);
      // printf("data : %s\n", data);
    } 
    fs_unmount(path);
    fs_deinit();
  } else {
    /* get input from console */
    char buf[MAX_SIZE];
    gets(buf);
    /* parse input*/
    cf_parse(buf);
  }

  end = clock();
  
  cpu = (end - start) / CLOCKS_PER_SEC;
  printf("%ld milliseconds elapsed\n", cpu);
  return 0;
}
