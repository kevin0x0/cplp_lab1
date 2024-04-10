#include "cst.h"
#include <stdarg.h>

#define LEVEL_PATTERN   ("  ")

CstGeneric* cst_create_generic(unsigned lineno, CstKind kind, const char* nodename, ...) {
  va_list childs;
  va_start(childs, nodename);
  va_list count;
  va_copy(count, childs);
  unsigned nchild = 0;
  while (va_arg(count, Cst*))
    ++nchild;
  va_end(count);
  CstGeneric* cst = (CstGeneric*)safe_alloc(sizeof (CstGeneric) + nchild * sizeof (Cst*));
  cst->nchild = nchild;
  cst->kind = kind;
  cst->nodename = nodename;
  for (size_t i = 0; i < nchild; ++i)
    cst->children[i] = va_arg(childs, Cst*);
  cst->lineno = nchild != 0 ? cst->children[0]->lineno : lineno;
  va_end(childs);
  return cst;
}

void cst_print(Cst* cst, unsigned currlevel, StrTbl* strtbl) {
  /* do not print infomation for non-terminal that with no children */
  if (!is_terminal(cst->kind) && ((CstGeneric*)cst)->nchild == 0)
    return;

  for (size_t i = 0; i < currlevel; ++i)
    printf(LEVEL_PATTERN);
  switch (cst->kind) {
    case CST_FLOAT: {
      printf("FLOAT: %f\n", ((CstFloat*)cst)->val);
      break;
    }
    case CST_INT: {
      printf("INT: %i\n", ((CstInt*)cst)->val);
      break;
    }
    case CST_TYPE: {
      printf("TYPE: %s\n", ((CstType*)cst)->val == TYPE_INT ? "int" : "float");
      break;
    }
    case CST_ID: {
      printf("ID: %s\n", strtbl_getstring(strtbl, ((CstId*)cst)->val));
      break;
    }
    case CST_SEMI: {
      printf("SEMI\n");
      break;
    }
    case CST_COMMA: {
      printf("COMMA\n");
      break;
    }
    case CST_ASSIGN: {
      printf("ASSIGN\n");
      break;
    }
    case CST_NE: {
      printf("NE\n");
      break;
    }
    case CST_EQ: {
      printf("EQ\n");
      break;
    }
    case CST_LE: {
      printf("LE\n");
      break;
    }
    case CST_LT: {
      printf("LT\n");
      break;
    }
    case CST_GE: {
      printf("GE\n");
      break;
    }
    case CST_GT: {
      printf("GT\n");
      break;
    }
    case CST_ADD: {
      printf("ADD\n");
      break;
    }
    case CST_SUB: {
      printf("SUB\n");
      break;
    }
    case CST_MUL: {
      printf("MUL\n");
      break;
    }
    case CST_DIV: {
      printf("DIV\n");
      break;
    }
    case CST_AND: {
      printf("AND\n");
      break;
    }
    case CST_OR: {
      printf("OR\n");
      break;
    }
    case CST_DOT: {
      printf("DOT\n");
      break;
    }
    case CST_NOT: {
      printf("NOT\n");
      break;
    }
    case CST_LP: {
      printf("LP\n");
      break;
    }
    case CST_RP: {
      printf("RP\n");
      break;
    }
    case CST_LB: {
      printf("LB\n");
      break;
    }
    case CST_RB: {
      printf("RB\n");
      break;
    }
    case CST_LC: {
      printf("LC\n");
      break;
    }
    case CST_RC: {
      printf("RC\n");
      break;
    }
    case CST_STRUCT: {
      printf("STRUCT\n");
      break;
    }
    case CST_RETURN: {
      printf("RETURN\n");
      break;
    }
    case CST_IF: {
      printf("IF\n");
      break;
    }
    case CST_ELSE: {
      printf("ELSE\n");
      break;
    }
    case CST_WHILE: {
      printf("WHILE\n");
      break;
    }
    default: {
      /* is non-terminal */
      CstGeneric* generic = (CstGeneric*)cst;
      /* print its infomation */
      printf("%s (%u)\n", generic->nodename, generic->lineno);
      for (size_t i = 0; i < generic->nchild; ++i)
        cst_print(generic->children[i], currlevel + 1, strtbl);
      break;
    }
  }
}
