%{
    #include <stdio.h>

    void yyerror(char*);
    int yylex(void);
%}

%union
{
    int num;
    char sym;
}

%token<num> NUMBER
%token PLUS MINUS MULTIPLY DIVIDE
%token EOL

%type<num> exp

%%
    input:
        | line input;

    line:
        exp EOL { printf("  =  %d\n", $1); }
        | EOL;

    exp:
        NUMBER { $$ = $1; }
        | NUMBER PLUS exp { $$ = $1 + $3; };
        | NUMBER MINUS exp { $$ = $1 - $3; };
        | NUMBER MULTIPLY exp { $$ = $1 * $3; };
	| NUMBER DIVIDE exp { $$ = $1 / $3; };
%%

int main(int argc, char* argv[])
{
    yyparse();

    return 0;
}

void yyerror(char* s)
{
    printf("Error: %s\n", s);
}
