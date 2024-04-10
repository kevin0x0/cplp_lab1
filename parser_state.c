#include "parser_state.h"
#include "cst.h"

void pstate_init(ParserState* pstate) {
  pstate->allcsts = NULL;
  pstate->nerror = 0;
  utils_oom_ifnull(pstate->strtbl = strtbl_create());
  pstate->noattrtokennode.error = pstate_appendcst(pstate, cst_create_noattrtoken(0, CST_ERROR));
}

void pstate_destroy(ParserState* pstate) {
  pstate->nerror = 0;
  strtbl_delete(pstate->strtbl);
  Cst* csts = pstate->allcsts;
  while (csts) {
    Cst* tmp = csts->next;
    free(csts);
    csts = tmp;
  }
}
