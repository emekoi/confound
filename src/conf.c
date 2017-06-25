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
	printf("%s\n", p->inst);
	return p;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    char *path = dirname(argv[1]);
    char *file = basename(argv[1]);
    fs_error(fs_setWritePath(path));
    fs_error(fs_mount(path));

    fs_FileListNode *list = fs_listDir(path);
    if (list) {
      int i = 1;
      fs_FileListNode *n = list;
      while (n) {
        // puts(n->name);
        i++;
        n = n->next;
      }
    } else {
      puts("uh oh");
    }
    /* check that file exists */
    if (fs_exists(file)) {
      /* read the file */
      size_t len;
      char *data = fs_read(file, &len);
      /* parase file */
      cf_parse(data);
    } 
    fs_freeFileList(list);
    fs_unmount(path);
    fs_deinit();
  } else {
    /* get input from console */
    char buf[MAX_SIZE];
    gets(buf);
    /* parse input */
    cf_parse(buf);
  }
  return 0;
}
