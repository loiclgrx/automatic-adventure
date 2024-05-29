/* symbol.c */

#include "global.hpp"

#define MAX_SYMBOLS 100 // size of symbol table

struct symentry symtable[MAX_SYMBOLS];
int nr_symbols = 0; // number of symbols in symtable

int lookup(const char *s) // returns position of entry for s, or -1 if not found
{
    for (int p = nr_symbols - 1; p >= 0; --p)
        if (strcmp(symtable[p].lexeme, s) == 0)
            return p;
    return -1;
}

int insert(const char *s, int token_type) // returns position of entry for s
{
    if (nr_symbols >= MAX_SYMBOLS)
        error("Symbol table full");
    symtable[nr_symbols].token_type = token_type;
    symtable[nr_symbols].lexeme = strdup(s);
    symtable[nr_symbols].value = 0;
    return nr_symbols++;
}
