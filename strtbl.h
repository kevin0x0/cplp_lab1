#ifndef _STRTBL_H_
#define _STRTBL_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define KLSTRTAB_EXTRA    (4096)

typedef struct tagStrTbl {
  char* stack;
  char* curr;
  char* end;
} StrTbl;

typedef uint32_t StringId;

StrTbl* strtbl_create(void);
void strtbl_delete(StrTbl* strtab);

static inline size_t strtbl_residual(StrTbl* strtab);
static inline size_t strtbl_capacity(StrTbl* strtab);
static inline size_t strtbl_size(StrTbl* strtab);

char* strtbl_grow(StrTbl* strtab, size_t extra);
static inline bool strtbl_checkspace(StrTbl* strtab, size_t space);
/* get a pointer to the top of the stack. */
static inline char* strtbl_allocstring(StrTbl* strtab, size_t size);
/* length includes the trailing '\0' */
static inline StringId strtbl_pushstring(StrTbl* strtab, size_t length);
static inline char* strtbl_newstring(StrTbl* strtab, const char* str);
/* get offset(id) of a string in the string table. */
static inline StringId strtbl_stringid(StrTbl* strtab, char* str);
/* get string by offset(id). */
static inline char* strtbl_getstring(StrTbl* strtab, size_t id);


static inline size_t strtbl_residual(StrTbl* strtab) {
  return strtab->end - strtab->curr;
}

static inline size_t strtbl_capacity(StrTbl* strtab) {
  return strtab->end - strtab->stack;
}

static inline size_t strtbl_size(StrTbl* strtab) {
  return strtab->curr - strtab->stack;
}

static inline bool strtbl_checkspace(StrTbl* strtab, size_t space) {
  return strtbl_residual(strtab) >= space;
}

static inline char* strtbl_allocstring(StrTbl* strtab, size_t size) {
  if (!strtbl_checkspace(strtab, size))
    return strtbl_grow(strtab, size);
  return strtab->curr;
}

static inline StringId strtbl_pushstring(StrTbl* strtab, size_t length) {
  StringId id = strtab->curr - strtab->stack;
  strtab->curr += length;
  return id;
}

static inline char* strtbl_newstring(StrTbl* strtab, const char* str) {
  int len = strlen(str) + 1;
  char* mystr = strtbl_allocstring(strtab, len);
  if (!mystr) return mystr;
  strcpy(mystr, str);
  strtbl_pushstring(strtab, len);
  return mystr;
}

static inline StringId strtbl_stringid(StrTbl* strtab, char* str) {
  assert(str >= strtab->stack && str <= strtab->curr);

  return str - strtab->stack;
}

static inline char* strtbl_getstring(StrTbl* strtab, size_t id) {
  assert(id <= strtbl_size(strtab));

  return strtab->stack + id;
}

#endif
