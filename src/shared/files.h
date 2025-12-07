#pragma once

#include "dynamic_array.h"
#include "static_array.h"
#include "strings.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>

static inline String read_entire_file(const char *path)
{
  String result = {0};

  FILE *file = fopen(path, "rb");
  if (!file) return result;

  fseek(file, 0, SEEK_END);
  s64 file_size = (s64)ftell(file);
  fseek(file, 0, SEEK_SET);

  result.items = (char *)malloc((u64)file_size);
  if (!result.items)
  {
    result = (String){0};
    goto out;
  }

  result.len = (u64)fread(result.items, 1, (u64)file_size, file);

out:
  fclose(file);
  return result;
}
