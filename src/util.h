#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define color_red "\x1b[31m"
#define color_reset "\x1b[0m"

#define ASSERT(cond, ...) do { \
  if (!(cond)) { \
    fprintf(stderr, "%s[ASSERTION FAILED]:%s %s:%d: %s(): %s; ", color_red, color_reset, __FILE__, __LINE__, __func__, #cond); \
  fprintf(stderr, __VA_ARGS__); \
  fprintf(stderr, "\n"); \
  exit(EXIT_FAILURE); \
  } \
} while(0);

#define CF_ERROR(program, position, ...) do { \
  fprintf(stderr, "%s[ERROR]:%s %s:%lu: ", color_red, color_reset, program->name, position); \
  fprintf(stderr, __VA_ARGS__); \
  fprintf(stderr, "\n"); \
  exit(EXIT_FAILURE); \
} while(0);

#define UNUSED(x)       ((void) (x))
#define MIN(a, b)       ((b) < (a) ? (b) : (a))
#define MAX(a, b)       ((b) > (a) ? (b) : (a))
#define CLAMP(x, a, b)  (MAX(a, MIN(x, b)))
#define LERP(a, b, p)   ((a) + ((b) - (a)) * (p))

#define GCINFO(clean, dirty) do { \
  printf("[GC %s]: CLEAN: %ld values \tDIRTY: %ld values \tTHRESHOLD: %ld values\n", __TIME__, clean, dirty, clean * 2); \
} while(0);

#endif
