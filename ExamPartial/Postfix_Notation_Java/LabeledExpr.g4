grammar LabeledExpr;

/* Syntax analizer */

prog: stat+;

stat:
	expr NEWLINE			# printExpr
	| ID '=' expr NEWLINE	# assign
	| NEWLINE				# blank;

expr:
	expr expr op = ('*' | '/') # MulDiv
	| expr expr op = ('+' | '-')	# AddSub
	| expr expr op = ('%' | '^')	# ModPow 
	| INT							# Int
	| ID							# Id
	| '(' expr ')'					# Parens;

/* Lexical analizer */

MUL: '*';
DIV: '/';
ADD: '+';
SUB: '-';
MOD: '%';
POW: '^';

ID: [a-zA-Z]+;
INT: [0-9]+;
NEWLINE: '\r'? '\n';
WS: [ \t]+ -> skip;