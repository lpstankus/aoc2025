#include "../shared/files.h"
#include "../shared/strings.h"
#include "../shared/types.h"

s32 modulo(s32 a, s32 b)
{
  s32 result = a % b;
  return (result < 0) ? (result + b) : result;
}

s32 part_one(String input)
{
  s32 ans = 0;
  s32 pointer = 50;

  String it = input;
  for (String line = next_line(&it); it.len != 0; line = next_line(&it))
  {
    s32 num = string_to_s32(SA_SLICE(line, 1, line.len));
    switch (DA_GET(line, 0))
    {
    case 'L':
      num *= -1;
      break;
    case 'R':
      break;
    default:
      assert(false);
    }
    pointer = modulo(pointer + num, 100);
    if (pointer == 0) ans += 1;
  }

  return ans;
}

s32 part_two(String input)
{
  s32 ans = 0;
  s32 pointer = 50;

  String it = input;
  for (String line = next_line(&it); line.len != 0; line = next_line(&it))
  {
    s32 num = string_to_s32(SA_SLICE(line, 1, line.len));

    while (num < 0 || 100 <= num)
    {
      ans += 1;
      num += (num < 0) ? 100 : -100;
    }
    assert(0 <= num && num < 100);

    switch (DA_GET(line, 0))
    {
    case 'L':
      num *= -1;
      if (pointer != 0 && pointer + num < 0) ans += 1;
      break;
    case 'R':
      if (pointer + num > 100) ans += 1;
      break;
    default:
      assert(false);
    }

    pointer = modulo(pointer + num, 100);
    if (pointer == 0) ans += 1;
  }

  return ans;
}

int main()
{
  String example = read_entire_file("./src/day01/example.txt");
  String input = read_entire_file("./src/day01/input.txt");

  printf("part one:\n");
  printf("example => %d\n", part_one(example));
  printf("input   => %d\n", part_one(input));

  printf("part two:\n");
  printf("example => %d\n", part_two(example));
  printf("input   => %d\n", part_two(input));

  return 0;
}
