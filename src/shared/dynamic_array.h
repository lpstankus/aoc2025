#pragma once

#include "static_array.h"
#include "types.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define DA_TYPE(type)                                                          \
  struct                                                                       \
  {                                                                            \
    type *items;                                                               \
    s64 len;                                                                   \
    s64 cap;                                                                   \
  }

#define DA_IT_IDX(da, idx) for (s64 idx = 0; (idx) < (s64)((da).len); (idx)++)
#define DA_IT_VAL(da, val)                                                     \
  for (typeof(*(da).items) val,                                                \
       *__ptr = (da).items,                                                    \
       *__end = (da).items + (da).len;                                         \
       __ptr < __end && ((val = *__ptr), 1);                                   \
       ++__ptr)

#define DA_GET(da, idx)                                                        \
  ({                                                                           \
    assert((idx) < (da).len);                                                  \
    (da).items[(idx)];                                                         \
  })

#define DA_SET(da, idx, val)                                                   \
  do                                                                           \
  {                                                                            \
    assert((idx) < (da).len);                                                  \
    (da).items[(idx)] = (val);                                                 \
  } while (0)

#define DA_SLICE(da, beg, val) ({ SA_SLICE(DA_DOWNGRADE(da), beg, val); })

#define DA_APPEND(da, val)                                                     \
  do                                                                           \
  {                                                                            \
    if ((da).cap == 0)                                                         \
    {                                                                          \
      (da).cap = 128;                                                          \
      (da).items = calloc((da).cap, sizeof(typeof(*(da).items)));              \
    }                                                                          \
    else if ((da).len >= (da).cap)                                             \
    {                                                                          \
      (da).cap *= 2;                                                           \
      (da).items =                                                             \
          realloc((da).items, sizeof(typeof(*(da).items)) * (da).cap);         \
    }                                                                          \
    (da).items[(da).len] = (val);                                              \
    (da).len += 1;                                                             \
  } while (0)

#define DA_RESERVE(da, cap)                                                    \
  do                                                                           \
  {                                                                            \
    if ((da).cap < cap)                                                        \
    {                                                                          \
      (da).cap = cap;                                                          \
      (da).items = realloc((da).items, sizeof(typeof(*(da).items) *(da).cap)); \
    }                                                                          \
  } while (0)

#define DA_CLONE(da)                                                           \
  ({                                                                           \
    typeof(da) __da = (da);                                                    \
    typeof(da) __clone;                                                        \
    __clone.cap = __da.cap;                                                    \
    __clone.len = __da.len;                                                    \
    __clone.items = calloc(__da.cap, sizeof(typeof(__da.items[0])));           \
    memcpy(__clone.items,                                                      \
           __da.items,                                                         \
           sizeof(typeof(__da.items[0])) * __da.len);                          \
    __clone;                                                                   \
  })

#define DA_DROP(da)                                                            \
  do                                                                           \
  {                                                                            \
    if ((da).items)                                                            \
    {                                                                          \
      free((da).items);                                                        \
      (da) = (typeof(da)){0};                                                  \
    }                                                                          \
  } while (0)

#define DA_DOWNGRADE(da)                                                       \
  ({                                                                           \
    typeof(da) __da = (da);                                                    \
    SA_TYPE(typeof(__da.items[0])) __sa;                                       \
    __sa.items = __da.items;                                                   \
    __sa.len = __da.len;                                                       \
    __sa;                                                                      \
  })
