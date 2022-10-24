%{
	/* Definitions */
%}

/* Rules */
%%

[0-9]+	{ printf("NUMBER\n"); }
\n	{ return 0; }
.	{ }

%%

int yywrap() { }
 
int main() {
	yylex();
	return 0;
} 
 
