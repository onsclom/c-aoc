#include "core.h"

#include <stdio.h>

void assert_fail(const char *file, i32 line, const char *expr) {
  fprintf(stderr, "assertion failed: %s\n  at %s:%d\n", expr, file, (int)line);
  __builtin_trap();
}

void *memset(void *s, i32 c, size_t n) {
  u8 *p = (u8 *)s;
  for (size_t i = 0; i < n; i++) {
    p[i] = (u8)c;
  }
  return s;
}

void *memcpy(void *dest, const void *src, size_t n) {
  u8 *d = (u8 *)dest;
  const u8 *s = (u8 *)src;
  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}

i32 memcmp(const void *s1, const void *s2, size_t n) {
  const u8 *a = (u8 *)s1;
  const u8 *b = (u8 *)s2;
  for (size_t i = 0; i < n; i++) {
    if (a[i] != b[i])
      return a[i] - b[i];
  }
  return 0;
}
