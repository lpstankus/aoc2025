#pragma once

#include "static_array.h"
#include "types.h"
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

static inline s32 string_to_s32(String string)
{
  char ch = string.items[string.len];
  string.items[string.len] = 0;
  s32 val = (s32)atoi(string.items);
  string.items[string.len] = ch;
  return val;
}

static inline s64 string_to_s64(String string)
{
  char ch = string.items[string.len];
  string.items[string.len] = 0;
  s64 val = (s64)atoll(string.items);
  string.items[string.len] = ch;
  return val;
}

static inline String s32_to_string(s32 val)
{
  char buffer[20]; // Enough for a 64-bit integer
  s32 len = (s32)snprintf(buffer, sizeof(buffer), "%d", val);

  String result = {
      .items = (char *)malloc(len + 1),
      .len = (u64)len,
  };

  memcpy(result.items, buffer, len);
  result.items[result.len] = 0;

  return result;
}

static inline String s64_to_string(s64 val)
{
  char buffer[20]; // Enough for a 64-bit integer
  s32 len = (s32)snprintf(buffer, sizeof(buffer), "%ld", val);

  String result = {
      .items = (char *)malloc(len + 1),
      .len = (u64)len,
  };

  memcpy(result.items, buffer, len);
  result.items[result.len] = 0;

  return result;
}
