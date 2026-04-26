#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

#define DECLARE_ARRAY(TYPE)                                                    \
  typedef struct {                                                             \
    TYPE *data;                                                                \
    size_t length;                                                             \
  } TYPE##_array;

DECLARE_ARRAY(u8)
DECLARE_ARRAY(u16)
DECLARE_ARRAY(u32)
DECLARE_ARRAY(u64)
DECLARE_ARRAY(i8)
DECLARE_ARRAY(i16)
DECLARE_ARRAY(i32)
DECLARE_ARRAY(i64)
DECLARE_ARRAY(f32)
DECLARE_ARRAY(f64)

void *memset(void *s, i32 c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
i32 memcmp(const void *s1, const void *s2, size_t n);

void assert_fail(const char *file, i32 line, const char *expr);

#undef assert
#define assert(cond)                                                           \
  ((cond) ? (void)0 : assert_fail(__FILE__, __LINE__, #cond))
