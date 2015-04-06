/**
 *
 * vhwmon - Virtual Hardware Monitor
 * Copyright (C) 2013  Vincenzo Frascino <gabrielknight4@gmail.com>
 *
 * This file is part of vhwmon.
 *
 * vhwmon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * vhwmon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with vhwmon.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
%{
#define YYSTYPE int /* yyparse() stack type */
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "vhwmon-lex.h"
%}
/* BISON Declarations */
%token NEWLINE NUMBER MAJOR MINOR PLUS MINUS SLASH ASTERISK LPAREN RPAREN

%{
	static int res;
	int yyerror(char *s);
%}

%code provides{
	int eval_exp(char *exp);
}

/* Grammar follows */
%%
input:	/* empty string */
	| input line
	;
line:	NEWLINE
	| expr NEWLINE			{ res = $1; }
	| expr MAJOR expr NEWLINE	{ if($1 > $3) res = 1; else res = 0; }
	| expr MINOR expr NEWLINE	{ if($1 < $3) res = 1; else res = 0; }
	;
expr:	expr PLUS term			{ $$ = $1 + $3; }
	| expr MINUS term		{ $$ = $1 - $3; }
	| term
	;
term:	term ASTERISK factor		{ $$ = $1 * $3; }
	| term SLASH factor		{ $$ = $1 / $3; }
	| factor
	;
factor:	LPAREN expr RPAREN		{ $$ = $2; }
	| NUMBER
	;
%%
/*--------------------------------------------------------*/
/* Additional C code */
/* Error processor for yyparse */
#include <stdio.h>
int yyerror(char *s) /* called by yyparse on error */
{
	printf("%s\n",s);
	return(0);
}

void scan_string(const char* str)
{
	yy_switch_to_buffer(yy_scan_string(str));
}

/*--------------------------------------------------------*/
/* The controlling function */
int eval_exp(char *exp)
{
	scan_string(exp);
	yyparse();
	yylex_destroy();
	
	return res;
}

