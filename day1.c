#include "aoc.c"

#define ARENA_SIZE 1024 * 1024
u8 arena_buffer[ARENA_SIZE] = {};
static Arena a = {
    .base = arena_buffer,
    .cap = ARENA_SIZE,
};

int main() {
  s8 input = read_file_as_s8(&a, s8_lit("day1-input.txt"));
  s8_array lines = s8_split_lines(&a, input);
  i32 dial = 50;
  i32 zero_end = 0;
  i32 zero_any = 0;
  for (size_t i = 0; i < lines.length; i++) {
    const s8 line = lines.data[i];
    u8 dir = line.data[0];
    assert(dir == 'L' || dir == 'R');
    i32 dist =
        s8_to_i32((s8){.data = line.data + 1, .length = line.length - 1});
    i32 step = dir == 'L' ? -1 : 1;
    for (i32 j = 0; j < dist; j++) {
      dial = ((dial + step) % 100 + 100) % 100;
      if (dial == 0)
        zero_any++;
    }
    if (dial == 0)
      zero_end++;
  }
  printf("part1: %d\n", zero_end);
  printf("part2: %d\n", zero_any);
}
