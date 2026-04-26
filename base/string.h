#pragma once

#include "arena.h"
#include "core.h"

typedef struct {
  u8 *data;
  size_t length;
} s8;

DECLARE_ARRAY(s8)

#define s8_lit(str) (s8){.data = (u8 *)(str), .length = sizeof(str) - 1}

bool s8_eq(s8 a, s8 b);
char *s8_to_cstr(Arena *a, s8 s);
s8_array s8_split_lines(Arena *a, s8 input);

i64 s8_to_i64_bounded(s8 s, i64 min, i64 max);
u64 s8_to_u64_bounded(s8 s, u64 max);
f64 s8_to_f64(s8 s);

i8 s8_to_i8(s8 s);
i16 s8_to_i16(s8 s);
i32 s8_to_i32(s8 s);
i64 s8_to_i64(s8 s);
u8 s8_to_u8(s8 s);
u16 s8_to_u16(s8 s);
u32 s8_to_u32(s8 s);
u64 s8_to_u64(s8 s);
f32 s8_to_f32(s8 s);

bool is_alpha(u8 c);
bool is_digit(u8 c);
bool is_alnum(u8 c);
