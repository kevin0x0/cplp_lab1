#ifndef _PARSER_STATE_H_
#define _PARSER_STATE_H_

#include "cst.h"
#include "strtbl.h"

typedef struct tagParserState {
  StrTbl* strtbl;
  Cst* allcsts;
  unsigned nerror;
  struct {
    Cst* error;
  } noattrtokennode;
} ParserState;

#define pstate_appendcst(pstate, cst)   pstate_appendcst_raw((pstate), (Cst*)(cst))

static inline Cst* pstate_appendcst_raw(ParserState* pstate, Cst* cst) {
  cst->next = pstate->allcsts;
  pstate->allcsts = cst;
  return cst;
}

void pstate_init(ParserState* pstate);
void pstate_destroy(ParserState* pstate);

#endif
