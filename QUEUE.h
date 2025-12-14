
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
typedef struct Vec {
  void *items;
  size_t start;
  size_t len;
  size_t end;
  size_t cap;
} Vec;

size_t vec_len(Vec *s) { return s->len; }
void vec_expand(Vec *s, size_t item_size) {
  size_t prev_cap = s->cap;
  void *prev = s->items;
  s->cap *= 2;
  s->items = malloc(item_size * s->cap);
  if (s->end <= s->start) {
    memcpy((char *)s->items, (char *)prev + s->start,
           (prev_cap - s->start) * item_size);
    memcpy(s->items + (prev_cap - s->start), (char *)prev, s->end * item_size);
  } else {
    memcpy((char *)s->items, (char *)prev + s->start, s->len * item_size);
  }
  s->start = 0;
  s->end = s->len;
  free(prev);
}
void vec_reset_vals(Vec *s, size_t item_size) {

  if (s->end < s->start) {
    memset((char *)s->items + s->start, 0, (s->cap - s->start) * item_size);
    memset((char *)s->items, 0, s->end * item_size);
  } else {
    memset((char *)s->items + s->start, 0, (s->end - s->start) * item_size);
  }
}
void vec_push_back(Vec *s, size_t item_size, void *item) {
  size_t len = s->len;
  if (len == s->cap) {
    vec_expand(s, item_size);
  }
  memcpy((char *)s->items + (s->end * item_size), item, item_size);

  s->len++;
  s->end++;
  if (s->end == s->cap) {
    s->end = 0;
  }
}

void vec_push_front(Vec *s, size_t item_size, void *item) {
  size_t len = s->len;
  if (len == s->cap) {
    vec_expand(s, item_size);
  }
  s->len++;
  s->start = s->start == 0 ? s->cap - 1 : s->start - 1;
  memcpy((char *)s->items + (s->start * item_size), item, item_size);
}
void *vec_pop_front(Vec *s, size_t elem_size) {
  if (s->len == 0) {
    return NULL;
  }
  void *tmp = (char *)s->items + (s->start * elem_size);
  s->start++;
  s->len--;
  if (s->start == s->cap) {
    s->start = 0;
  }
  return tmp;
}

void *vec_pop_back(Vec *s, size_t item_size) {
  if (s->len == 0) {
    return NULL;
  }
  s->end = s->end == 0 ? s->cap - 1 : s->end - 1;
  s->len--;
  return (char *)s->items + (s->end * item_size);
}
void *vec_get(Vec *s, size_t item_size, size_t idx) {
  if (s->len <= idx) {
    return NULL;
  }
  size_t pos = s->start + idx;
  if (pos >= s->cap)
    pos -= s->cap;
  return (char *)s->items + (pos * item_size);
}
size_t vec_get_idx(Vec *s, size_t item_size, void *item) {
  size_t len = s->len;
  size_t idx = 0;
  if (len == 0)
    return SIZE_MAX;

  if (s->start < s->end) {
    for (size_t i = s->start; i < s->end; i++) {

      if (memcmp((char *)s->items + (i * item_size), item, item_size) == 0) {
        return idx;
      }
      idx++;
    }
  } else {
    for (size_t i = s->start; i < s->cap; i++) {
      if (memcmp((char *)s->items + (i * item_size), item, item_size) == 0) {
        return idx;
      }
      idx++;
    }
    for (size_t i = 0; i < s->end; i++) {
      if (memcmp((char *)s->items + (i * item_size), item, item_size) == 0) {
        return idx;
      }
      idx++;
    }
  }
  return SIZE_MAX;
}
int vec_contains(Vec *s, size_t item_size, void *item) {
  size_t len = s->len;
  if (len == 0)
    return 0;

  if (s->start < s->end) {
    for (size_t i = s->start; i < s->end; i++) {
      if (memcmp((char *)s->items + (i * item_size), item, item_size) == 0)
        return 1;
    }
  } else {
    for (size_t i = s->start; i < s->cap; i++) {
      if (memcmp((char *)s->items + (i * item_size), item, item_size) == 0)
        return 1;
    }
    for (size_t i = 0; i < s->end; i++) {
      if (memcmp((char *)s->items + (i * item_size), item, item_size) == 0)
        return 1;
    }
  }
  return 0;
}
void vec_swap_remove_idx(Vec *s, size_t item_size, size_t idx) {
  /*if there is one item left we just pop it*/
  if (s->len == 1) {
    vec_pop_back(s, item_size);
    return;
  }

  void *idx_item = vec_get(s, item_size, idx);
  if (idx_item == NULL) {
    return;
  }
  memcpy(idx_item, vec_pop_back(s, item_size), item_size);
}
void vec_swap_remove(Vec *s, size_t item_size, void *item) {
  /*if there is one item left we just pop it*/
  if (s->len == 1) {
    vec_pop_back(s, item_size);
    return;
  }

  if (item == NULL) {
    return;
  }
  memcpy(item, vec_pop_back(s, item_size), item_size);
}
void *vec_get_item(Vec *s, size_t item_size, void *item) {
  /*if there is one item left we just pop it*/
  if (s->len == 0) {
    return NULL;
  }

  size_t idx = vec_get_idx(s, item_size, item);
  return vec_get(s, item_size, idx);
}
Vec vec_new(size_t cap, size_t item_size) {
  return (Vec){.items = malloc(item_size * cap),
               .start = 0,
               .end = 0,
               .len = 0,
               .cap = cap};
}

#define VEC_NEW(type, cap) vec_new(cap, sizeof(type))
// creating these as macros
#define VEC_PUSH_FRONT(type, s, item)                                          \
  vec_push_front(s, sizeof(type), (type *)item)
#define VEC_PUSH_BACK(type, s, item)                                           \
  vec_push_back(s, sizeof(type), (type *)item)
#define VEC_POP_FRONT(type, s) (type *)vec_pop_front(s)
#define VEC_POP_BACK(type, s) (type *)vec_pop_back(s)

#define VEC_GET(type, s, idx) (type *)vec_get(s, sizeof(type), idx)
#define VEC_GET_ITEM(type, s, item)                                            \
  (type *)vec_get_item(s, sizeof(type), (type *)item)

#define VEC_GET_IDX(type, s, idx) vec_get_idx(s, sizeof(type), idx)
#define VEC_SWAP_REMOVE_IDX(type, s, idx)                                      \
  vec_swap_remove_idx(s, sizeof(type), idx)
#define VEC_SWAP_REMOVE(type, s, item)                                         \
  vec_swap_remove(s, sizeof(type), (type *)item)

#define VEC_CONTAINS(type, s, item) vec_contains(s, sizeof(type), (type *)item)

#define VEC_RESET_VALS(type, s) vec_reset_vals(s, sizeof(type))