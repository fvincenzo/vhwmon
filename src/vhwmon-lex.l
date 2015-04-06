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
// lexer.l -- From tcalc: a simple calculator program
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vhwmon-yacc.h"
#include "vhwmon-variables.h"
extern YYSTYPE yylval;
%}

%option noyywrap
%option nounput
%option noinput
delim [ \t]
whitesp {delim}+
digit [0-9]
number {digit}+
letteral [a-zA-Z0-9]
variable {letteral}+
%%
{number} { sscanf(yytext, "%d", &yylval); return NUMBER;}
{variable} { char variable[32]; sscanf(yytext, "%s", variable); yylval = find_variable(variable); return NUMBER; }
"+" { return PLUS; }
"-" { return MINUS; }
"/" { return SLASH; }
"*" { return ASTERISK; }
"(" { return LPAREN; }
")" { return RPAREN; }
"<" { return MINOR; }
">" { return MAJOR; }
"\n" { return NEWLINE; }
{whitesp} { /* No action and no return */}

