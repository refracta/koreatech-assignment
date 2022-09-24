/* English -> American */
%%
"colour" { printf("color"); }
"flavour" { printf("flavor"); }
"clever" { printf("smart"); }
"smart" { printf("elegant"); }
"conservative" { printf("liberal"); }
"luggage" { printf("baggage"); }
"lift" { printf("elevator"); }
"underground" { printf("subway"); }
"autumn" { printf("fall"); }
"jumper" { printf("sweater"); }
. { printf("%s", yytext); }
%%
