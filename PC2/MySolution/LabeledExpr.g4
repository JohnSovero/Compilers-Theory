grammar LabeledExpr;

/* Syntax analizer */

prog: stat+ EOF;

// top 
//	::= definition 
//  | external 
//  | expr 
stat:
	expr 			# printExpr
	| ID '=' expr        	# assign
    | definition            # DefTop
    | external              # ExternTop;

// definition 
//  ::= 'def' prototype expression
definition:
	'def' prototype expr    #Def;

// protopype 
//	::= id '(' (E|id (',' id)*) ')'
prototype:
	ID '(' (ID (ID)*)? ')'  	    #PrototypeExpr;

// external ::= 'extern' prototype
external:
	'extern' prototype #Extern;

expr:
	expr op = ('*' | '/') expr		# MulDiv
	| expr op = ('+' | '-') expr	# AddSub
	| NUM							# Int
	| ID							# Id
	| '(' expr ')'					# Parens;

/* Lexical analizer */

MUL: '*';
DIV: '/';
ADD: '+';
SUB: '-';

ID: [a-zA-Z]+;
NUM: [-+]? ([0-9]* [.][0-9]+ | [0-9]+ [.]?) ([eE][-+]? [0-9]+)?;
WS: [ \t\n\r]+ -> skip;