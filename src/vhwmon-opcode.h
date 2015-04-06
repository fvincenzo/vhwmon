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
#ifndef VHWMON_OPCODE_H_INCLUDED
#define VHWMON_OPCODE_H_INCLUDED

/* OPCODE Implementation */
/* Each function returns execution status */

/* Print Screen Functions */
int opcode_print(char *buf);
int opcode_printl(char *buf);
int opcode_printh(char *buf);

/* Let Function */
int opcode_let(char *buf);

/* For Next function */
int opcode_for(int program_counter, char *buf);
int opcode_next(int program_counter, char *buf);

/* Goto Instruction */
int opcode_goto(char *buf);

#endif /* VHWMON_OPCODE_H_INCLUDED */
