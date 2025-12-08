#include "../shared/files.h"
#include "../shared/strings.h"
#include "../shared/types.h"

typedef DA_TYPE(char) Bank;
typedef DA_TYPE(Bank) Battery;

Battery parse_input(String input)
{
  Battery result = {0};

  String it = input;
  for (String line = next_line(&it); line.len != 0; line = next_line(&it))
  {
    Bank bank = {0};

    DA_IT_VAL(line, ch)
    {
      DA_APPEND(bank, ch - '0');
    }

    DA_APPEND(result, bank);
  }

  return result;
}

s64 largest_joltage(Bank bank, s32 n)
{
  s32 *idxs = calloc(n, sizeof(s32));

  for (s32 idx = 0; idx < n; idx++)
  {
    s32 curr = (idx == 0) ? 0 : idxs[idx - 1] + 1;
    s32 off = (n - 1 - idx);
    for (s32 i = curr + 1; i < bank.len - off; i++)
    {
      if (DA_GET(bank, curr) < DA_GET(bank, i))
      {
        curr = i;
      }
    }
    idxs[idx] = curr;
  }

  s64 ans = 0;
  s64 pot = 1;
  for (s32 i = n - 1; i >= 0; i--)
  {
    ans += DA_GET(bank, idxs[i]) * pot;
    pot *= 10;
  }
  free(idxs);

  return ans;
}

s64 solve(String input, s32 n)
{
  Battery bat = parse_input(input);

  s64 ans = 0;

  DA_IT_VAL(bat, bank)
  {
    ans += largest_joltage(bank, n);
  }

  return ans;
}

s32 main()
{
  String example = read_entire_file("./src/day03/example.txt");
  String input = read_entire_file("./src/day03/input.txt");

  printf("part one:\n");
  printf("example -> %ld\n", solve(example, 2));
  printf("input   -> %ld\n", solve(input, 2));

  printf("part two:\n");
  printf("example -> %ld\n", solve(example, 12));
  printf("input   -> %ld\n", solve(input, 12));

  return 0;
}
