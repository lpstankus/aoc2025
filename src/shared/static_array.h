#pragma once

#include "dynamic_array.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define SA_TYPE(type)                                                          \
  struct                                                                       \
  {                                                                            \
    type *items;                                                               \
    int len;                                                                   \
  }

#define SA_GET(sa, idx)                                                        \
  ({                                                                           \
    assert((idx) < (sa).len);                                                  \
    (sa).items[(idx)];                                                         \
  })

#define SA_SET(sa, idx, val)                                                   \
  do                                                                           \
  {                                                                            \
    assert((idx) < (sa).len);                                                  \
    (sa).items[(idx)] = (val);                                                 \
  } while (0)

#define SA_SLICE(sa, beg, end)                                                 \
  ({                                                                           \
    assert(0 <= beg && beg < sa.len);                                          \
    assert(0 < end && end <= sa.len);                                          \
    assert(beg <= end);                                                        \
    typeof(sa) slice;                                                          \
    slice.items = sa.items + beg;                                              \
    slice.len = end - beg;                                                     \
    slice;                                                                     \
  })

#define SA_IT_IDX(sa, idx) for (int idx = 0; (idx) < ((sa).len); (idx)++)
#define SA_IT_VAL(sa, val)                                                     \
  for (typeof(*(sa).items) val,                                                \
       *__ptr = (sa).items,                                                    \
       *__end = (sa).items + (sa).len;                                         \
       __ptr < __end && ((val = *__ptr), 1);                                   \
       ++__ptr)

#define SA_CLONE(sa)                                                           \
  ({                                                                           \
    typeof(sa) __sa = (sa);                                                    \
    typeof(sa) __clone;                                                        \
    __clone.len = __sa.len;                                                    \
    __clone.items = calloc(__sa.len, sizeof(typeof(__sa.items[0])));           \
    memcpy(__clone.items,                                                      \
           __sa.items,                                                         \
           sizeof(typeof(__sa.items[0])) * __sa.len);                          \
    __clone;                                                                   \
  })

#define SA_DROP(sa)                                                            \
  do                                                                           \
  {                                                                            \
    if ((sa).items)                                                            \
    {                                                                          \
      free((sa).items);                                                        \
      (sa) = (typeof(sa)){0};                                                  \
    }                                                                          \
  } while (0)

#define SA_UPGRADE(sa)                                                         \
  ({                                                                           \
    typeof(sa) __sa = (sa);                                                    \
    DA_TYPE(typeof(__sa.items[0])) __da;                                       \
    __da.items = __sa.items;                                                   \
    __da.len = __sa.len;                                                       \
    __da.cap = __sa.len; /* We assume that len == capacity on static arrays */ \
    __da;                                                                      \
  })
