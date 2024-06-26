CC = gcc
CFLAGS = -Wall -Wextra -g
LEX = flex
YACC = bison
LIBS = -lfl -ly

parser : mycc.o cst.o parser_state.o strtbl.o cmmlex.o cmm.tab.o
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)

mycc.o : mycc.c mycc.h parser_state.h utils.h strtbl.h cst.h cmm.tab.h
	$(CC) -c $< $(CFLAGS)

cst.o : cst.c cst.h utils.h
	$(CC) -c $< $(CFLAGS)

parser_state.o : parser_state.c parser_state.h cst.h strtbl.h utils.h
	$(CC) -c $< $(CFLAGS)

strtbl.o : strtbl.c strtbl.h
	$(CC) -c $< $(CFLAGS)

cmmlex.o : cmmlex.c mycc.h parser_state.h utils.h strtbl.h cst.h cmm.tab.h
	$(CC) -c $< $(CFLAGS)

cmmlex.c : cmm.l mycc.h parser_state.h utils.h strtbl.h cst.h cmm.tab.h
	$(LEX) -o $@ $<

cmm.tab.o : cmm.tab.c cmm.tab.h
	$(CC) -c $< $(CFLAGS)

cmm.tab.c cmm.tab.h : cmm.y mycc.h parser_state.h utils.h strtbl.h cst.h
	$(YACC) -d $<

.PHONY: clean

clean :
	$(RM) *.o parser cmm.tab.c cmm.tab.h cmmlex.c
