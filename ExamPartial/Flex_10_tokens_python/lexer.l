%{

#define COMP 256
#define ID 257
#define IF 258
#define ELSE 259
#define NUM 260
#define ELIF 261
#define BREAK 262
#define CONTINUE 263
#define WHILE 264
#define FOR 265
#define DEF 266
#define TRY 267
#define RETURN 268
%}

%option noyywrap

COMP (<=?)|(>=?)|(!=)|(==)
ID [a-zA-Z_][a-zA-Z0-9_]*
NUM [0-9]+

%%

{COMP}			    { return COMP; }
if					{ return IF; }
else				{ return ELSE; }
elif				{ return ELIF; }
break				{ return BREAK; }
continue			{ return CONTINUE; }
while               { return WHILE; }
for                 { return FOR; }
def                 { return DEF; }
try                 { return TRY; }
return              { return RETURN; }

{NUM}				{ return NUM; }
{ID}				{ return ID; }
[ \n\r\t]		{}
.						{}

%%

int main(int argc, char **argv) {
	++argv, --argc;
	if (argc > 0) {
		yyin = fopen(argv[0], "r");
    } else {
		yyin = stdin;
	}

	int token;
	while ((token = yylex())) {
    printf("Lexem (%d): %s\n", token, yytext);
	}

	return 0;
}