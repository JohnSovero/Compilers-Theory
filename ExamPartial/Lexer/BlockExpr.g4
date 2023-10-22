grammar BlockExpr;

program: stat+;

function
    : (UNSIGNED | SIGNED)? (INT | LONG)+ ID '(' (UNSIGNED| SIGNED)? (INT | LONG)+ ID (',' ID)* ')' '{' block '}'
    ;

block
    : (stat)+
    ;

stat
    : IF '(' expr ')' '{' expr '}'
	| ELSE '{' expr '}'
	| (UNSIGNED | SIGNED)? (INT | LONG)? ID '=' expr ';'
	| expr
	| function;

expr
    : ID '(' expr (',' expr)* ')'
	| expr op = ('*' | '/') expr
	| expr op = ('+' | '-') expr
	| expr '==' expr
	| RETURN expr ';'
	| '(' expr ')'
	| NUM
	| ID;

EQ: '=';
EQ2: '==';
COMMA: ',';
SEMI: ';';
LPAREN: '(';
RPAREN: ')';
MUL: '*';
DIV: '/';
ADD: '+';
SUB: '-';

UNSIGNED: 'unsigned';
SIGNED: 'signed';
INT: 'int';
LONG: 'long';
IF: 'if';
ELSE: 'else';
RETURN: 'return';

NUM: [0-9]+;
ID: [a-zA-Z_][a-zA-Z_0-9]*;

WS: [ \n\r\t]+ -> skip;