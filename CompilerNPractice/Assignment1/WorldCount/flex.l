/* declaration and option settings */
%{
    void addWord(char *text);
    void addNewLine(void);
    void addChar(void);

    int chars = 0;
    int words = 0;
    int lines = 0;
%}

/* a list of patterns and actions */
%%
[a-zA-Z]+   addWord(yytext);
\n          addNewLine();
.           addChar();
%%

/* c code */
void addWord(char *text) {
    ++words;
    chars += strlen(text);
}

void addNewLine(void) {
    ++chars;
    ++lines;
}

void addChar(void) {
    ++chars;
}

int main(void) {
    yylex();
    printf("%8d%8d%8d\n", lines, words, chars);
    return 0;
}