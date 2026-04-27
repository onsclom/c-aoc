#include "aoc.c"

#define ARENA_SIZE (1 * 1024 * 1024)
u8 arena_buffer[ARENA_SIZE] = {};
static Arena a = {
    .base = arena_buffer,
    .cap = ARENA_SIZE,
};

static u64 max_joltage(s8 line, size_t k) {
  assert(line.length >= k);
  u8 stack[256];
  assert(line.length <= sizeof(stack));
  size_t top = 0;
  size_t removals = line.length - k;
  for (size_t i = 0; i < line.length; i++) {
    u8 d = (u8)(line.data[i] - '0');
    while (top > 0 && stack[top - 1] < d && removals > 0) {
      top--;
      removals--;
    }
    stack[top++] = d;
  }
  u64 n = 0;
  for (size_t i = 0; i < k; i++)
    n = n * 10 + stack[i];
  return n;
}

int main() {
  s8 input = read_file_as_s8(&a, s8_lit("day3-input.txt"));
  s8_array lines = s8_split_lines(&a, input);

  u64 part1 = 0;
  u64 part2 = 0;
  for (size_t i = 0; i < lines.length; i++) {
    part1 += max_joltage(lines.data[i], 2);
    part2 += max_joltage(lines.data[i], 12);
  }

  printf("part1: %llu\n", (unsigned long long)part1);
  printf("part2: %llu\n", (unsigned long long)part2);
}
