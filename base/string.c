#include "string.h"

bool s8_eq(s8 a, s8 b) {
  if (a.length != b.length)
    return false;
  return memcmp(a.data, b.data, a.length) == 0;
}

char *s8_to_cstr(Arena *a, s8 s) {
  char *cstr = arena_alloc(a, s.length + 1);
  memcpy(cstr, s.data, s.length);
  cstr[s.length] = 0;
  return cstr;
}

s8_array s8_split_lines(Arena *a, s8 input) {
  size_t count = 0;
  for (size_t i = 0; i < input.length; i++) {
    if (input.data[i] == '\n')
      count++;
  }
  if (input.length > 0 && input.data[input.length - 1] != '\n')
    count++;

  s8 *lines = arena_alloc(a, count * sizeof(s8));
  size_t idx = 0;
  size_t start = 0;
  for (size_t i = 0; i < input.length; i++) {
    if (input.data[i] == '\n') {
      size_t end = i;
      if (end > start && input.data[end - 1] == '\r')
        end--;
      lines[idx++] = (s8){.data = input.data + start, .length = end - start};
      start = i + 1;
    }
  }
  if (start < input.length) {
    size_t end = input.length;
    if (end > start && input.data[end - 1] == '\r')
      end--;
    lines[idx++] = (s8){.data = input.data + start, .length = end - start};
  }
  return (s8_array){.data = lines, .length = count};
}

i64 s8_to_i64_bounded(s8 s, i64 min, i64 max) {
  assert(s.length > 0);

  size_t i = 0;
  bool negative = false;
  if (s.data[0] == '-') {
    negative = true;
    i = 1;
  } else if (s.data[0] == '+') {
    i = 1;
  }
  assert(i < s.length);

  u64 mag = 0;
  for (; i < s.length; i++) {
    u8 c = s.data[i];
    assert(is_digit(c));
    mag = mag * 10 + (u64)(c - '0');
  }

  i64 value;
  if (negative) {
    assert(mag <= (u64)INT64_MAX + 1);
    value = (mag == (u64)INT64_MAX + 1) ? INT64_MIN : -(i64)mag;
  } else {
    assert(mag <= (u64)INT64_MAX);
    value = (i64)mag;
  }

  assert(value >= min && value <= max);
  return value;
}

u64 s8_to_u64_bounded(s8 s, u64 max) {
  assert(s.length > 0);

  size_t i = 0;
  if (s.data[0] == '+')
    i = 1;
  assert(i < s.length);

  u64 value = 0;
  for (; i < s.length; i++) {
    u8 c = s.data[i];
    assert(is_digit(c));
    u64 next = value * 10 + (u64)(c - '0');
    assert(next >= value);
    value = next;
  }

  assert(value <= max);
  return value;
}

f64 s8_to_f64(s8 s) {
  assert(s.length > 0);

  size_t i = 0;
  f64 sign = 1.0;
  if (s.data[0] == '-') {
    sign = -1.0;
    i = 1;
  } else if (s.data[0] == '+') {
    i = 1;
  }
  assert(i < s.length);

  f64 value = 0.0;
  bool has_digits = false;
  while (i < s.length && is_digit(s.data[i])) {
    value = value * 10.0 + (f64)(s.data[i] - '0');
    i++;
    has_digits = true;
  }

  if (i < s.length && s.data[i] == '.') {
    i++;
    f64 scale = 0.1;
    while (i < s.length && is_digit(s.data[i])) {
      value += scale * (f64)(s.data[i] - '0');
      scale *= 0.1;
      i++;
      has_digits = true;
    }
  }

  assert(has_digits);

  if (i < s.length && (s.data[i] == 'e' || s.data[i] == 'E')) {
    i++;
    i32 esign = 1;
    if (i < s.length && s.data[i] == '-') {
      esign = -1;
      i++;
    } else if (i < s.length && s.data[i] == '+') {
      i++;
    }
    assert(i < s.length && is_digit(s.data[i]));
    i32 exp = 0;
    while (i < s.length && is_digit(s.data[i])) {
      exp = exp * 10 + (i32)(s.data[i] - '0');
      i++;
    }
    f64 mult = 1.0;
    for (i32 e = 0; e < exp; e++)
      mult *= 10.0;
    if (esign < 0)
      value /= mult;
    else
      value *= mult;
  }

  assert(i == s.length);
  return sign * value;
}

i8 s8_to_i8(s8 s) { return (i8)s8_to_i64_bounded(s, INT8_MIN, INT8_MAX); }
i16 s8_to_i16(s8 s) { return (i16)s8_to_i64_bounded(s, INT16_MIN, INT16_MAX); }
i32 s8_to_i32(s8 s) { return (i32)s8_to_i64_bounded(s, INT32_MIN, INT32_MAX); }
i64 s8_to_i64(s8 s) { return s8_to_i64_bounded(s, INT64_MIN, INT64_MAX); }
u8 s8_to_u8(s8 s) { return (u8)s8_to_u64_bounded(s, UINT8_MAX); }
u16 s8_to_u16(s8 s) { return (u16)s8_to_u64_bounded(s, UINT16_MAX); }
u32 s8_to_u32(s8 s) { return (u32)s8_to_u64_bounded(s, UINT32_MAX); }
u64 s8_to_u64(s8 s) { return s8_to_u64_bounded(s, UINT64_MAX); }
f32 s8_to_f32(s8 s) { return (f32)s8_to_f64(s); }

bool is_alpha(u8 c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_digit(u8 c) { return c >= '0' && c <= '9'; }

bool is_alnum(u8 c) { return is_alpha(c) || is_digit(c) || c == '_'; }
