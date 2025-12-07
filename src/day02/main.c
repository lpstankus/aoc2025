#include "../shared/files.h"
#include "../shared/strings.h"
#include "../shared/types.h"

typedef struct
{
  s64 lo;
  s64 hi;
} Range;

typedef DA_TYPE(Range) DA_RANGE;

DA_RANGE parse_input(String input)
{
  DA_RANGE result = {0};

  String it = input;
  for (String range = next_split(&it, ','); range.len != 0;
       range = next_split(&it, ','))
  {
    s64 lo = string_to_s64(next_split(&range, '-'));
    s64 hi = string_to_s64(range);

    Range val = {.lo = lo, .hi = hi};
    DA_APPEND(result, val);
  }

  return result;
}

bool invalid_id_one(s64 id)
{
  String id_str = s64_to_string(id);

  if (id_str.len % 2 != 0) return false;

  String a = SA_SLICE(id_str, 0, id_str.len / 2);
  String b = SA_SLICE(id_str, id_str.len / 2, id_str.len);

  return string_equal(a, b);
}

s64 part_one(String input)
{
  DA_RANGE commands = parse_input(input);

  s64 ans = 0;

  DA_IT_VAL(commands, val)
  {
    for (s64 id = val.lo; id <= val.hi; id++)
    {
      if (invalid_id_one(id)) ans += id;
    }
  }

  return ans;
}

bool invalid_id_two(s64 id)
{
  String id_str = s64_to_string(id);
  for (s64 len = 1; len <= id_str.len / 2; len++)
  {
    if (id_str.len % len != 0) continue;

    bool valid = false;

    String base = SA_SLICE(id_str, 0, len);
    for (s64 ptr = len; ptr < id_str.len; ptr += len)
    {
      String test = SA_SLICE(id_str, ptr, ptr + len);
      if (!string_equal(base, test))
      {
        valid = true;
        break;
      }
    }

    if (!valid) return true;
  }

  return false;
}

s64 part_two(String input)
{
  DA_RANGE commands = parse_input(input);

  s64 ans = 0;

  DA_IT_VAL(commands, val)
  {
    for (s64 id = val.lo; id <= val.hi; id++)
    {
      if (invalid_id_two(id)) ans += id;
    }
  }

  return ans;
}

int main()
{
  String example = read_entire_file("./src/day02/example.txt");
  String input = read_entire_file("./src/day02/input.txt");

  printf("part one:\n");
  printf("example -> %ld\n", part_one(example));
  printf("input   -> %ld\n", part_one(input));

  printf("part two:\n");
  printf("example -> %ld\n", part_two(example));
  printf("input   -> %ld\n", part_two(input));

  return 0;
}
