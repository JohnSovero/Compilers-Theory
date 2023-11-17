grammar LabeledExpr;

/* Syntax analizer */

prog: 
	top EOF;

// top 
//	::= definition 
//  | external 
//  | expression | ';'
top:
	definition 	  #DefTop
	| external 	  #ExternTop
	| expression  #ExprTop;

// definition 
//  ::= 'def' prototype expression
definition:
	'def' prototype expression  #Def;

// protopype 
//	::= id '(' (E|id (',' id)*) ')'
prototype:
	ID '(' (ID (ID)*)? ')'  	            #PrototypeExpr;

// expression 
//	::= primary binoprhs
expression:
	expression op = ('*' | '/') expression   # MulDiv
	| expression op = ('+' | '-') expression # AddSub
	| NUM									 # Int
	| ID									 # Id
	| '(' expression ')'				 	 # Parens;

// external ::= 'extern' prototype
external:
	'extern' prototype #Extern;

/* Lexical analizer */

MUL: '*';
ADD: '+';
SUB: '-';

ID: [a-zA-Z]+;
NUM: [-+]? ([0-9]* [.][0-9]+ | [0-9]+ [.]?) ([eE][-+]? [0-9]+)?;
WS: [ \t\n\r]+ -> skip;