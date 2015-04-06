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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vhwmon-variables.h"
#include "vhwmon-utilities.h"
#include "vhwmon-yacc.h"
#include "vhwmon-loops.h"
#include "vhwmon-debug.h"

/* Print Screen Functions */
int opcode_print(char *buf)
{
	int status = 0;
	char *pch;

	if(strstr(buf, "\"") != NULL) {
		pch = strtok (buf, "\"");
		printf("%s", pch);
	} else
		printf("%d", find_variable(buf));

	return status;
}

int opcode_printl(char *buf)
{
	int status = 0;
	char *pch;

	if(strstr(buf, "\"") != NULL) {
		pch = strtok (buf, "\"");
		printf("%s\n", pch);
	}

	return status;
}

int opcode_printh(char *buf)
{
	int status = 0;

	printf("0x%x\n", find_variable(buf));

	return status;
}

/* Let Function */
int opcode_let(char *buf)
{
	int status = 0;
	int res = 0;
	char *name;
	char *value;
	
	if(strstr(buf, "=") != NULL) {
		name = strtok (buf, "=");
		value = strtok (NULL, " ");
		str_addnewline(value);
		res = eval_exp(value);
		update_variable(name, res);
	} else
		status = 1;
	
	return status;
}

/* For Next function */
int opcode_for(int program_counter, char *buf)
{
	int pcounter = 0;
	int res = 0;
	
	/* Check if the loop already exists */
	if(find_end(program_counter) == INVALID_LOOP) {
		add_entry(program_counter);
	}
	
	/* Evaluate For Condition */
	str_addnewline(buf);
	res = eval_exp(buf);
	
	if(res) {
		/* Condition Valid = Execute loop */
		pcounter = program_counter;
	} else {
		/* Condition Invalid = Exit loop */
		pcounter = find_end(program_counter);
	}
		
	return pcounter;	
}

int opcode_next(int program_counter, char *buf)
{
	int pcounter = 0;
	int local_var = 0;
	int loop_status = 0;

	/* Add End Of Loop */
	add_end(program_counter);

	/* Find For Entry */
	loop_status = find_entry(program_counter);

	/* loop_status != INVALID_LOOP means Legal Loop */
	if (loop_status != INVALID_LOOP) {
		/* Update Variable */
		local_var = find_variable(buf) + 1;
		update_variable(buf, local_var);
	
		/* Change Program Flow */
		pcounter = loop_status - 1;
	} else {
		pcounter = program_counter + 1;
	}
	
	return pcounter;	
}

/* Goto Instruction */
int opcode_goto(char *buf)
{
	int l_number = 0;

	l_number = atoi(buf);

	return l_number;
}





