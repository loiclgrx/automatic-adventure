/* language.lex */

%{
    #include <stdio.h>
    #include "global.hpp"
    extern int yyparse();
    extern int yylex(void);
    extern void yyerror(const char*);
    extern int lineno = 1;
    int id_number;
    int symbol(const char* s);
%}

%option noyywrap

%%

"="         { return '='; }
"?"         { return '?'; }
":"         { return ':'; }
"|"         { return '|'; }
"&"         { return '&'; }
"<"         { return '<'; }
">"         { return '>'; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"%"         { return '%'; }
"^"         { return '^'; }
"div"       { return DIV; }
"mod"       { return MOD; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"print"     { return PRINT; }
"read"      { return READ; }
"{"         { return '{'; }
"}"         { return '}'; }
[0-9]+      { yylval.i = atoi(yytext); return NUM; }
[a-zA-Z]+   { return symbol(yytext); }
";"         { return ';'; }
"("         { return '('; }
")"         { return ')'; }
"!"         { return DONE; }
[ \t]       { /* Ignore spaces and tabs */ }
\n          { lineno++; }
.           { fprintf(stderr, "Unrecognized character: %s\n", yytext); }

%%

int symbol(const char *s)
{
    id_number = lookup(s);
    if (id_number == -1)
    {
        id_number = insert(s, ID);
    }
    yylval.i = id_number;
    return symtable[id_number].token_type;
}