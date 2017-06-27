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

cf_Program *cf_new_program(char *name, size_t len) {
  cf_Program *p = (cf_Program *)calloc(1, sizeof(cf_Program));
  p->inst = (char *)calloc(len, sizeof(char));
  p->mem = (char *)calloc(MAX_SIZE, sizeof(char));
  p->name = name;
  p->len = len;
  p->dp = 0;
  return p;
}

void cf_close_program(cf_Program *program) {
  free(program->inst);
  free(program->mem);
  free(program);
}

cf_Program *cf_parse_program(char *name, char *source) {
	cf_Program *p = cf_new_program(name, strlen(source));
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

size_t *cf_compute_jumptable(cf_Program *program) {
  cf_Program *p = program;
  size_t *jmp_table = calloc(p->len, sizeof(size_t));
  
  for (p->ic = 0; p->ic < p->len; p->ic++) {
    switch (*(p->inst + p->ic)) {
      case '[': {
        int bracket_nesting = 1;
        size_t seek = p->ic;

        while (bracket_nesting && ++seek < p->len) {
          if (*(p->inst + seek) == ']') {
            bracket_nesting--;
          } else if (*(p->inst + seek) == '[') {
            bracket_nesting++;
          }
        }
        if (!bracket_nesting) {
          jmp_table[p->ic] = seek;
          jmp_table[seek] = p->ic;
          break;
        } else {
          CF_ERROR(program, seek, "unmatched '['");
        }
        break;
      } default: {
        break;
      }
    }
  }
  return jmp_table;
}

void cf_run_program(cf_Program *program) {
  cf_Program *p = program;
  size_t *jmp_table = cf_compute_jumptable(p);

  for (p->ic = 0; p->ic <= p->len; p->ic++) {
    switch (*(p->inst + p->ic)) {
      case '>': {
        p->dp++;
        break;
      } case '<': {
        p->dp--;
        break;
      } case '+': {
        p->mem[p->dp]++;
        break;
      } case '-': {
        p->mem[p->dp]--;
        break;
      } case '.': {
        putchar(p->mem[p->dp]);
        break;
      } case ',': {
        p->mem[p->dp] = getchar();
        break;
      } case '[': {
        if (p->mem[p->dp] == 0) {
          p->ic = jmp_table[p->ic];
        }
        break;
      } case ']': {
        if (p->mem[p->dp] != 0) {
          p->ic = jmp_table[p->ic];
        }
        break;
      } default: {
        break;
      }
    }
  }
  free(jmp_table);
}

int main(int argc, char **argv) {
  clock_t start, end, cpu;
  start = clock();
  cf_Program *program;

  if (argc > 1) {
    char *path = dirname(concat("./", strip(argv[1]), NULL));
    char *file = basename(concat("./", strip(argv[1]), NULL));
    printf("\nexe : %s\n", argv[0]);
    printf("path : %s\n", path);
    printf("file : %s\n\n", file);

    fs_error(fs_mount(path));
    fs_error(fs_setWritePath(path));
    /* check that file exists */
    if (fs_exists(file)) {
      /* read the file */
      size_t len;
      char *data = fs_read(file, &len);
      /* parse file */
      program = cf_parse_program(file, data);
      cf_run_program(program);
      cf_close_program(program);
    } 
    fs_unmount(path);
    fs_deinit();
  } else {
    /* get input from console */
    char buf[MAX_SIZE];
    gets(buf);
    /* parse input */
    program = cf_parse_program("stdin", buf);
    cf_run_program(program);
    cf_close_program(program);
  }


  end = clock();
  cpu = (end - start) / CLOCKS_PER_SEC;
  printf("\n\n%ld seconds elapsed\n", cpu);
  return 0;
}
