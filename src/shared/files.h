#pragma once

#include "dynamic_array.h"
#include "static_array.h"
#include "strings.h"
#include <stdio.h>
#include <stdlib.h>

static inline String read_entire_file(const char *path)
{
  String result = {0};

  FILE *file = fopen(path, "rb");
  if (!file) return result;

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  result.items = (char *)malloc(file_size);
  if (!result.items)
  {
    result = (String){0};
    goto out;
  }

  result.len = fread(result.items, 1, file_size, file);

out:
  fclose(file);
  return result;
}
