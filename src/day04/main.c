#include "../shared/files.h"
#include "../shared/strings.h"
#include "../shared/types.h"

typedef String Row;
typedef DA_TYPE(Row) Diagram;

Diagram parse_input(String input)
{
  Diagram result = {0};

  String it = input;
  for (String line = next_line(&it); line.len != 0; line = next_line(&it))
  {
    DA_APPEND(result, line);
  }

  return result;
}

s64 part_one(String input)
{
  Diagram diag = parse_input(input);

  s64 ans = 0;

  SA_IT_IDX(diag, i)
  {
    String row = DA_GET(diag, i);
    SA_IT_IDX(row, j)
    {
      s32 count = 0;
      for (s32 m = -1; m <= 1; m++)
      {
        for (s32 n = -1; n <= 1; n++)
        {
          if (n == 0 && m == 0) continue;
          s32
        }
      }
    }
  }

  return ans;
}

s32 main()
{
  String example = read_entire_file("./src/day03/example.txt");
  String input = read_entire_file("./src/day03/input.txt");

  printf("part one:\n");
  printf("example -> %ld\n", part_one(example));
  printf("input   -> %ld\n", part_one(input));

  return 0;
}
