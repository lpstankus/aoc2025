#pragma once

#include "static_array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef SA_TYPE(char) String;

static inline String next_split(String *string, char split)
{
  String result = {
      .items = string->items,
      .len = 0,
  };

  while (string->len > 0)
  {
    if (SA_GET(*string, 0) == split) break;
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

static inline String next_line(String *string)
{
  return next_split(string, '\n');
}

static inline bool string_equal(String a, String b)
{
  if (a.len != b.len) return false;
  return memcmp(a.items, b.items, a.len) == 0;
}

static inline void print_string(String string)
{
  SA_IT_VAL(string, val) printf("%c", val);
}

static inline int string_to_int(String string)
{
  char ch = string.items[string.len];
  string.items[string.len] = 0;
  int val = atoi(string.items);
  string.items[string.len] = ch;
  return val;
}

static inline long long string_to_longlong(String string)
{
  char ch = string.items[string.len];
  string.items[string.len] = 0;
  long long val = atoll(string.items);
  string.items[string.len] = ch;
  return val;
}

static inline String int_to_string(int val)
{
  char buffer[20]; // Enough for a 64-bit integer
  int len = snprintf(buffer, sizeof(buffer), "%d", val);

  String result = {
      .items = (char *)malloc(len + 1),
      .len = len,
  };

  memcpy(result.items, buffer, len);
  result.items[result.len] = 0;

  return result;
}

static inline String longlong_to_string(long long val)
{
  char buffer[20]; // Enough for a 64-bit integer
  int len = snprintf(buffer, sizeof(buffer), "%lld", val);

  String result = {
      .items = (char *)malloc(len + 1),
      .len = len,
  };

  memcpy(result.items, buffer, len);
  result.items[result.len] = 0;

  return result;
}
