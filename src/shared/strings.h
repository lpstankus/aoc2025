#pragma once

#include "static_array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef SA_TYPE(char) String;

static inline String next_line(String *string)
{
  String result = {
      .items = string->items,
      .len = 0,
  };

  while (string->len > 0)
  {
    if (string->items[0] == '\n') break;
    string->items += 1;
    string->len -= 1;
    result.len += 1;
  }

  if (string->len > 0)
  {
    string->items += 1;
    string->len -= 1;
  }

  return result;
}

static inline void print_string(String string)
{
  SA_IT_VAL(string, val) printf("%c", val);
}

static inline int parse_int(String string)
{
  char ch = string.items[string.len];
  string.items[string.len] = 0;
  int val = atoi(string.items);
  string.items[string.len] = ch;
  return val;
}
