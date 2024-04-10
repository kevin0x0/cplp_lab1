#include "mycc.h"
#include "cmm.tab.h"
#include "parser_state.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


void mycc_error(const char* error_type, unsigned lineno, const char* format, ...) {
  ++parser_state->nerror;
  fprintf(stderr, "error type %s at line %d: ", error_type, lineno);
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  fputc('\n', stderr);
  va_end(args);
}

extern int yylineno;
void yyerror(const char* msg) {
  mycc_error("B", yylineno, "%s", msg);
}

ParserState globalstate;
ParserState* parser_state = &globalstate;

extern FILE* yyin;
int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage %s <file name>\n", argv[0]);
    return 0;
  }
  FILE* input = fopen(argv[1], "r");
  if (!input) {
    fprintf(stderr, "can not open file: %s\n", argv[1]);
    return 1;
  }
  yyin = input;
  pstate_init(parser_state);
  yyparse();
  pstate_destroy(parser_state);
  fclose(input);
  return 0;
}
