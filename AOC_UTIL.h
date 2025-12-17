#include <stdint.h>
#include <stdio.h>

typedef struct FileBuffer {
  char *buffer;
  size_t len;
} FileBuffer;
FileBuffer read_file(FILE *aoc);

FILE *open_file_from_args(int argc, char **argv);

int16_t mod(int16_t a, int16_t b);

uint64_t get_num(char ch);

char convert_to_char(uint64_t num);
int dec_str(char *str, size_t len);
// int inc_str(char *str);
size_t repeats_pat(const char *str, size_t str_len, const char *pat,
                   size_t pat_len);
int str_cmp_as_num(const char *str1, size_t len1, const char *str2,
                   size_t len2);

uint64_t max(uint64_t val1, uint64_t val2);
uint64_t min(uint64_t val1, uint64_t val2);

#define STACK_DEF(type)                                                        \
  typedef struct Stack##type {                                                 \
    type *items;                                                               \
    size_t len;                                                                \
    size_t cap;                                                                \
  } Stack##type;                                                               \
                                                                               \
  void stack_push##type(Stack##type *s, type item) {                           \
    if (s->len == s->cap) {                                                    \
      s->cap *= 2;                                                             \
      s->items = realloc(s->items, sizeof(*s->items) * s->cap);                \
    }                                                                          \
    s->items[s->len] = item;                                                   \
    s->len++;                                                                  \
  }                                                                            \
  type *stack_pop##type(Stack##type *s) {                                      \
    if (s->len == 0) {                                                         \
      return NULL;                                                             \
    }                                                                          \
    s->len -= 1;                                                               \
    return s->items + s->len;                                                  \
  }                                                                            \
  type *stack_get##type(Stack##type *s, size_t idx) {                          \
    if (s->len <= idx) {                                                       \
      return NULL;                                                             \
    }                                                                          \
    return s->items + s->len;                                                  \
  }                                                                            \
  int stack_contains##type(Stack##type *s, type item) {                        \
    for (size_t idx = 0; idx < s->len; idx++) {                                \
      if (s->items[idx] == item) {                                             \
        return 1;                                                              \
      }                                                                        \
    }                                                                          \
    return 0;                                                                  \
  }                                                                            \
  Stack##type stack_new##type(size_t cap) {                                    \
    return (Stack##type){                                                      \
        .items = malloc(sizeof(type) * cap), .len = 0, .cap = cap};            \
  }

#define STACK(type) Stack##type
#define STACK_NEW(type, cap) stack_new##type(cap)
// creating these as macros
#define STACK_PUSH(type, s, item) stack_push##type(s, item)
#define STACK_POP(type, s) (type *)stack_pop##type(s)
#define STACK_GET(type, s, idx) (type *)stack_get##type(s, idx)

#define STACK_CONTAINS(type, item) stack_contains##type(s, item)

#define VEC_DEF(type)                                                          \
  typedef struct Vec##type {                                                   \
    type *items;                                                               \
    size_t start;                                                              \
    size_t len;                                                                \
    size_t end;                                                                \
    size_t cap;                                                                \
  } Vec##type;                                                                 \
                                                                               \
  size_t vec_len##type(Vec##type *s) { return s->len; }                        \
  void vec_expand##type(Vec##type *s) {                                        \
    size_t prev_cap = s->cap;                                                  \
    type *prev = s->items;                                                     \
    s->cap *= 2;                                                               \
    s->items = malloc(sizeof(*s->items) * s->cap);                             \
                                                                               \
    if (s->end <= s->start) {                                                  \
      memcpy(s->items, prev + s->start,                                        \
             (prev_cap - s->start) * sizeof(*s->items));                       \
      memcpy(s->items + (prev_cap - s->start), prev,                           \
             s->end * sizeof(*s->items));                                      \
    } else {                                                                   \
      memcpy(s->items, prev + s->start, s->len * sizeof(*s->items));           \
    }                                                                          \
    s->start = 0;                                                              \
    s->end = s->len;                                                           \
    free(prev);                                                                \
  }                                                                            \
  void vec_reset_vals##type(Vec##type *s) {                                    \
                                                                               \
    if (s->end < s->start) {                                                   \
      memset(s->items + s->start, 0, (s->cap - s->start) * sizeof(*s->items)); \
      memset(s->items, 0, s->end * sizeof(*s->items));                         \
    } else {                                                                   \
      memset(s->items + s->start, 0, (s->end - s->start) * sizeof(*s->items)); \
    }                                                                          \
  }                                                                            \
  void vec_push_back##type(Vec##type *s, type item) {                          \
    size_t len = s->len;                                                       \
    if (len == s->cap) {                                                       \
      vec_expand##type(s);                                                     \
    }                                                                          \
                                                                               \
    s->items[s->end] = item;                                                   \
    s->len++;                                                                  \
    s->end++;                                                                  \
    if (s->end == s->cap) {                                                    \
      s->end = 0;                                                              \
    }                                                                          \
  }                                                                            \
                                                                               \
  void vec_push_front##type(Vec##type *s, type item) {                         \
    size_t len = s->len;                                                       \
    if (len == s->cap) {                                                       \
      vec_expand##type(s);                                                     \
    }                                                                          \
    s->len++;                                                                  \
    s->start = s->start == 0 ? s->cap - 1 : s->start - 1;                      \
    s->items[s->start] = item;                                                 \
  }                                                                            \
  type *vec_pop_front##type(Vec##type *s) {                                    \
    if (s->len == 0) {                                                         \
      return NULL;                                                             \
    }                                                                          \
    type *tmp = s->items + s->start;                                           \
    s->start++;                                                                \
    s->len--;                                                                  \
    if (s->start == s->cap) {                                                  \
      s->start = 0;                                                            \
    }                                                                          \
    return tmp;                                                                \
  }                                                                            \
                                                                               \
  type *vec_pop_back##type(Vec##type *s) {                                     \
    if (s->len == 0) {                                                         \
      return NULL;                                                             \
    }                                                                          \
    s->end = s->end == 0 ? s->cap - 1 : s->end - 1;                            \
    s->len--;                                                                  \
    return s->items + s->end;                                                  \
  }                                                                            \
  type *vec_get##type(Vec##type *s, size_t idx) {                              \
    if (s->len <= idx) {                                                       \
      return NULL;                                                             \
    }                                                                          \
    size_t pos = s->start + idx;                                               \
    if (pos >= s->cap)                                                         \
      pos -= s->cap;                                                           \
    return s->items + pos;                                                     \
  }                                                                            \
  size_t vec_get_idx##type(Vec##type *s, type item) {                          \
    size_t len = s->len;                                                       \
    size_t idx = 0;                                                            \
    if (len == 0)                                                              \
      return SIZE_MAX;                                                         \
                                                                               \
    if (s->start < s->end) {                                                   \
      for (size_t i = s->start; i < s->end; i++) {                             \
        if (s->items[i] == item) {                                             \
          return idx;                                                          \
        }                                                                      \
        idx++;                                                                 \
      }                                                                        \
    } else {                                                                   \
      for (size_t i = s->start; i < s->cap; i++) {                             \
        if (s->items[i] == item) {                                             \
          return idx;                                                          \
        }                                                                      \
        idx++;                                                                 \
      }                                                                        \
      for (size_t i = 0; i < s->end; i++) {                                    \
        if (s->items[i] == item) {                                             \
          return idx;                                                          \
        }                                                                      \
        idx++;                                                                 \
      }                                                                        \
    }                                                                          \
    return SIZE_MAX;                                                           \
  }                                                                            \
  int vec_contains##type(Vec##type *s, type item) {                            \
    size_t len = s->len;                                                       \
    if (len == 0)                                                              \
      return 0;                                                                \
                                                                               \
    if (s->start < s->end) {                                                   \
      for (size_t i = s->start; i < s->end; i++) {                             \
        if (s->items[i] == item)                                               \
          return 1;                                                            \
      }                                                                        \
    } else {                                                                   \
      for (size_t i = s->start; i < s->cap; i++) {                             \
        if (s->items[i] == item)                                               \
          return 1;                                                            \
      }                                                                        \
      for (size_t i = 0; i < s->end; i++) {                                    \
        if (s->items[i] == item)                                               \
          return 1;                                                            \
      }                                                                        \
    }                                                                          \
    return 0;                                                                  \
  }                                                                            \
  void vec_swap_remove_idx##type(Vec##type *s, size_t idx) {                   \
    /*if there is one item left we just pop it*/                               \
    if (s->len == 1) {                                                         \
      vec_pop_back##type(s);                                                   \
      return;                                                                  \
    }                                                                          \
                                                                               \
    type *idx_item = vec_get##type(s, idx);                                    \
    if (idx_item == NULL) {                                                    \
      return;                                                                  \
    }                                                                          \
    *idx_item = *vec_pop_back##type(s);                                        \
  }                                                                            \
  void vec_swap_remove##type(Vec##type *s, type *item) {                       \
    /*if there is one item left we just pop it*/                               \
    if (s->len == 1) {                                                         \
      vec_pop_back##type(s);                                                   \
      return;                                                                  \
    }                                                                          \
                                                                               \
    if (item == NULL) {                                                        \
      return;                                                                  \
    }                                                                          \
    *item = *vec_pop_back##type(s);                                            \
  }                                                                            \
  type *vec_get_item##type(Vec##type *s, type item) {                          \
    /*if there is one item left we just pop it*/                               \
    if (s->len == 0) {                                                         \
      return NULL;                                                             \
    }                                                                          \
                                                                               \
    size_t idx = vec_get_idx##type(s, item);                                   \
    return vec_get##type(s, idx);                                              \
  }                                                                            \
  Vec##type vec_new##type(size_t cap) {                                        \
    return (Vec##type){.items = malloc(sizeof(type) * cap),                    \
                       .start = 0,                                             \
                       .end = 0,                                               \
                       .len = 0,                                               \
                       .cap = cap};                                            \
  }

#define VEC(type) Vec##type
#define VEC_NEW(type, cap) vec_new##type(cap)
// creating these as macros
#define VEC_PUSH_FRONT(type, s, item) vec_push_front##type(s, item)
#define VEC_PUSH_BACK(type, s, item) vec_push_back##type(s, item)
#define VEC_POP_FRONT(type, s) vec_pop_front##type(s)
#define VEC_POP_BACK(type, s) vec_pop_back##type(s)

#define VEC_GET(type, s, idx) (type *)vec_get##type(s, idx)
#define VEC_GET_ITEM(type, s, item) (type *)vec_get_item##type(s, item)

#define VEC_GET_IDX(type, s, idx) (type *)vec_get_idx##type(s, idx)
#define VEC_SWAP_REMOVE_IDX(type, s, idx) vec_swap_remove_idx##type(s, idx)
#define VEC_SWAP_REMOVE(type, s, item) vec_swap_remove##type(s, item)

#define VEC_CONTAINS(type, s, item) vec_contains##type(s, item)

#define VEC_RESET_VALS(type, s) vec_reset_vals##type(s)
