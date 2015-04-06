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
#ifndef VHWMON_INSTRUCTIONS_H_INCLUDED
#define VHWMON_INSTRUCTIONS_H_INCLUDED

/* Opcode Definition */
#define PROGRAM	0x1
#define	END	0x2
#define PRINT	0x3
#define PRINTL	0x4
#define PRINTH	0x5
#define	INPUT	0x6
#define	LET	0x7
#define	FOR	0x8
#define	NEXT	0x9
#define	GOTO	0x10
#define REM	0x11

/* decode_instruction returns 0 on END program */
int decode_instruction(char *buf);
/* Execute Program */
int execute_instructions(void);

#endif /* VHWMON_INSTRUCTIONS_H_INCLUDED */
