#include "../shared/files.h"
#include "../shared/strings.h"

int modulo(int a, int b)
{
  int result = a % b;
  return (result < 0) ? (result + b) : result;
}

int part_one(String input)
{
  int ans = 0;
  int pointer = 50;

  String it = input;
  for (String line = next_line(&it); it.len != 0; line = next_line(&it))
  {
    int num = parse_int(SA_SLICE(line, 1, line.len));
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

int part_two(String input)
{
  int ans = 0;
  int pointer = 50;

  String it = input;
  for (String line = next_line(&it); line.len != 0; line = next_line(&it))
  {
    int num = parse_int(SA_SLICE(line, 1, line.len));

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
