#include "aoc.c"

#define ARENA_SIZE (1 * 1024 * 1024)
u8 arena_buffer[ARENA_SIZE] = {};
static Arena a = {
    .base = arena_buffer,
    .cap = ARENA_SIZE,
};

static u64 sweep(u8 *grid, size_t rows, size_t cols, bool remove) {
  u64 n = 0;
  for (size_t r = 0; r < rows; r++) {
    for (size_t c = 0; c < cols; c++) {
      if (grid[r * cols + c] != '@')
        continue;
      u8 neighbors = 0;
      for (i32 dr = -1; dr <= 1; dr++) {
        for (i32 dc = -1; dc <= 1; dc++) {
          if (dr == 0 && dc == 0)
            continue;
          i64 nr = (i64)r + dr;
          i64 nc = (i64)c + dc;
          if (nr < 0 || nr >= (i64)rows || nc < 0 || nc >= (i64)cols)
            continue;
          if (grid[nr * cols + nc] == '@')
            neighbors++;
        }
      }
      if (neighbors < 4) {
        n++;
        if (remove)
          grid[r * cols + c] = '.';
      }
    }
  }
  return n;
}

int main() {
  s8 input = read_file_as_s8(&a, s8_lit("day4-input.txt"));
  s8_array lines = s8_split_lines(&a, input);

  size_t rows = lines.length;
  size_t cols = lines.data[0].length;

  u8 *grid = arena_alloc(&a, rows * cols);
  for (size_t r = 0; r < rows; r++) {
    assert(lines.data[r].length == cols);
    memcpy(grid + r * cols, lines.data[r].data, cols);
  }

  u64 part1 = sweep(grid, rows, cols, false);

  u64 part2 = 0;
  for (;;) {
    u64 removed = sweep(grid, rows, cols, true);
    if (removed == 0)
      break;
    part2 += removed;
  }

  printf("part1: %llu\n", (unsigned long long)part1);
  printf("part2: %llu\n", (unsigned long long)part2);
}
