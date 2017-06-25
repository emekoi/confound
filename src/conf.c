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
    puts(path);
    fs_error(fs_setWritePath(path));
    fs_error(fs_mount(path));

    fs_FileListNode *list = fs_listDir(path);
    if (list) {
      // puts("hjk");
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

    // puts(basename(argv[1]));
    if (fs_exists(argv[1])) {
      puts(basename(argv[1]));
      size_t len;
      char *data = fs_read(basename(argv[1]), &len);
      puts(data);
    } 
    fs_freeFileList(list);
    fs_unmount(path);
    fs_deinit();
  } else {
    char buf[MAX_SIZE];
    gets(buf);
    cf_parse(buf);
  }
  return 0;
}
