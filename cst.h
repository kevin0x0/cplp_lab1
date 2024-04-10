#ifndef _CST_H_
#define _CST_H_

#include "strtbl.h"
#include "utils.h"

#include <stdint.h>
#include <stdlib.h>
#define CstHeader Cst* next; CstKind kind; unsigned lineno

typedef int32_t Int;
typedef float Float;

typedef enum tagType {
  TYPE_INT,
  TYPE_FLOAT
} Type;

typedef enum tagCstKind {
  CST_ERROR,
  CST_INT,
  CST_FLOAT,
  CST_TYPE,
  CST_ID,
  CST_SEMI,
  CST_COMMA,
  CST_ASSIGN,
  CST_NE,
  CST_EQ,
  CST_LE,
  CST_LT,
  CST_GE,
  CST_GT,
  CST_ADD,
  CST_SUB,
  CST_MUL,
  CST_DIV,
  CST_AND,
  CST_OR,
  CST_DOT,
  CST_NOT,
  CST_LP,
  CST_RP,
  CST_LB,
  CST_RB,
  CST_LC,
  CST_RC,
  CST_STRUCT,
  CST_RETURN,
  CST_IF,
  CST_ELSE,
  CST_WHILE,

  CST_Program,
  CST_ExtDefList,
  CST_ExtDef,
  CST_ExtDecList,

  CST_Specifier,
  CST_StructSpecifier,
  CST_OptTag,
  CST_Tag,

  CST_VarDec,
  CST_FunDec,
  CST_VarList,
  CST_ParamDec,
  CST_CompSt,

  CST_StmtList,
  CST_Stmt,
  CST_DefList,
  CST_Def,
  CST_DecList,
  CST_Dec,
  CST_Exp,
  CST_Args
} CstKind;

#define is_terminal(kind)         ((kind) <= CST_WHILE)
#define is_noattrtoken(kind)      ((kind) >= CST_SEMI && (kind) <= CST_WHILE)

#define make_cstkind(macro)       (CST_##macro)

#define make_kindstrpair(macro)   make_cstkind(macro), #macro

typedef struct tagCst Cst;
struct tagCst {
  CstHeader;
};

typedef struct tagCstInt {
  CstHeader;
  Int val;
} CstInt;

typedef struct tagCstFloat {
  CstHeader;
  Float val;
} CstFloat;

typedef struct tagCstType {
  CstHeader;
  Type val;
} CstType;

typedef struct tagCstId {
  CstHeader;
  StringId val;
} CstId;

typedef struct tagCstGeneric {
  CstHeader;
  unsigned nchild;
  const char* nodename;
  Cst* children[];
} CstGeneric;

typedef struct tagCstNoAttrToken {
  CstHeader;
} CstNoAttrToken;

static inline void* safe_alloc(size_t size) {
  void* p = malloc(size);
  utils_oom_ifnull(p);
  return p;
}

#define cstalloc(csttype)         (csttype*)safe_alloc(sizeof (csttype))

/* children must terminated with NULL.
 * for 'generic', the parameter 'lineno'
 * is only used when the number of children is 0. */
CstGeneric* cst_create_generic(unsigned lineno, CstKind kind, const char* nodename, ...);
void cst_print(Cst* cst, unsigned currlevel, StrTbl* strtbl);

static inline CstInt* cst_create_int(unsigned lineno, Int val) {
  CstInt* cst = cstalloc(CstInt);
  cst->kind = make_cstkind(INT);
  cst->lineno = lineno;
  cst->val = val;
  return cst;
}

static inline CstFloat* cst_create_float(unsigned lineno, Float val) {
  CstFloat* cst = cstalloc(CstFloat);
  cst->kind = make_cstkind(FLOAT);
  cst->lineno = lineno;
  cst->val = val;
  return cst;
}

static inline CstType* cst_create_type(unsigned lineno, Type val) {
  CstType* cst = cstalloc(CstType);
  cst->kind = make_cstkind(TYPE);
  cst->lineno = lineno;
  cst->val = val;
  return cst;
}

static inline CstId* cst_create_id(unsigned lineno, StringId val) {
  CstId* cst = cstalloc(CstId);
  cst->kind = make_cstkind(ID);
  cst->lineno = lineno;
  cst->val = val;
  return cst;
}

static inline CstNoAttrToken* cst_create_noattrtoken(unsigned lineno, CstKind kind) {
  CstNoAttrToken* cst = cstalloc(CstNoAttrToken);
  cst->kind = kind;
  cst->lineno = lineno;
  return cst;
}

#endif
