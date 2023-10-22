grammar PythonExpr;

program
    : stat+
    ;

def 
    : 'def' ID '(' ID (',' ID)* ')' ':' NEWLINE block 
    ;

block
    : simple_stmts
    ;

simple_stmts
    : (INDENT stat)+
    ;

stat: ID '=' expr NEWLINE # Assign
    | expr NEWLINE # Expression
    | def # Function
    | func # CallFunction
    | NEWLINE # Blank;

expr
    : expr op = ('*'|'/') expr # MulDiv
    | expr op = ('+'|'-') expr # AddSub
    | INT # Int
    | ID # Id
    | '(' expr ')' # Parens;

func 
    : ID '(' expr (',' expr)* ')'
    ;

AND : 'and' ;
OR : 'or' ;
NOT : 'not' ;
EQ : '=' ;
COMMA : ',' ;
SEMI : ';' ;
LPAREN : '(' ;
RPAREN : ')' ;
MUL: '*';
DIV: '/';
ADD: '+';
SUB: '-';

INT : [0-9]+ ;
ID: [a-zA-Z_][a-zA-Z_0-9]* ;

WS: [ \r]+ -> skip ;
NEWLINE: '\r'? '\n';
INDENT: '%' ;