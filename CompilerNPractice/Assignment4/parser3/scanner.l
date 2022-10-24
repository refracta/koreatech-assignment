%{
    #include "parser.tab.h"
%}

%%
[0-9]+ { yylval.num = atoi(yytext); return NUMBER; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULTIPLY; }
"/" { return DIVIDE; }
[\t]  { /* Ignore tab space */ }
\n { return EOL; }
" "   { /* Ignore white spaces */ }
. { printf("Mystery character '%c'\n", *yytext); }
%%

int yywrap() { }
