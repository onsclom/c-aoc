#include <stdio.h>

#include "base/base_inc.c"

s8 read_file_as_s8(Arena *a, s8 path) {
  char *cpath = s8_to_cstr(a, path);

  FILE *f = fopen(cpath, "rb");
  assert(f);

  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  fseek(f, 0, SEEK_SET);

  u8 *data = arena_alloc(a, (size_t)size);
  assert(fread(data, 1, (size_t)size, f) == (size_t)size);
  fclose(f);

  return (s8){.data = data, .length = (size_t)size};
}
