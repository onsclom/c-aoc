#include "aoc.c"

#define ARENA_SIZE (1 * 1024 * 1024)
u8 arena_buffer[ARENA_SIZE] = {};
static Arena a = {
    .base = arena_buffer,
    .cap = ARENA_SIZE,
};

static s8 to_digits(u64 n, u8 *buf) {
  size_t d = 0;
  u8 tmp[20];
  while (n > 0) {
    tmp[d++] = (u8)(n % 10);
    n /= 10;
  }
  for (size_t i = 0; i < d; i++)
    buf[i] = tmp[d - 1 - i];
  return (s8){.data = buf, .length = d};
}

static bool repeats_at(s8 digits, size_t b) {
  for (size_t i = b; i < digits.length; i++) {
    if (digits.data[i] != digits.data[i - b])
      return false;
  }
  return true;
}

int main() {
  s8 input = read_file_as_s8(&a, s8_lit("day2-input.txt"));
  while (input.length > 0 && (input.data[input.length - 1] == '\n' ||
                              input.data[input.length - 1] == '\r'))
    input.length--;

  u64 part1 = 0;
  u64 part2 = 0;

  size_t start = 0;
  for (size_t i = 0; i <= input.length; i++) {
    if (i != input.length && input.data[i] != ',')
      continue;
    s8 piece = {.data = input.data + start, .length = i - start};
    start = i + 1;
    if (piece.length == 0)
      continue;
    size_t dash = 0;
    while (dash < piece.length && piece.data[dash] != '-')
      dash++;
    assert(dash < piece.length);
    u64 lo = s8_to_u64((s8){.data = piece.data, .length = dash});
    u64 hi = s8_to_u64((s8){.data = piece.data + dash + 1,
                            .length = piece.length - dash - 1});

    u8 buf[20];
    for (u64 id = lo; id <= hi; id++) {
      s8 digits = to_digits(id, buf);
      if (digits.length % 2 == 0 && repeats_at(digits, digits.length / 2))
        part1 += id;
      for (size_t b = 1; b < digits.length; b++) {
        if (digits.length % b == 0 && repeats_at(digits, b)) {
          part2 += id;
          break;
        }
      }
    }
  }

  printf("part1: %llu\n", (unsigned long long)part1);
  printf("part2: %llu\n", (unsigned long long)part2);
}
