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
#include <stdlib.h>
#include <string.h>
#include "vhwmon-utilities.h"
#include "vhwmon-instructions.h"
#include "vhwmon-opcode.h"

#define PROGRAM_ALIVE	1
#define PROGRAM_END	0

struct instruction
{
	/* Number Position */
	int l_number;
	/* Opcode */
	int opcode;
	/* Buffer */
	char buffer[256];
};

/* Instructions Array */
static struct instruction i_array[256];

/* Program Counter */
static int program_counter = 0;

/* Instruction Counter */
static int instruction_counter = 0;

/* Instruction Decoder */
int i_decode(char *instruction)
{
	int opcode = 0;
	
	/* 
	 * If Instruction is null the program must terminate
	 * immediately.
	 */
	if (instruction == NULL)
		opcode = END;
	else {
		/* Convert Instruction to Lower Case */
		str_tolower(instruction);
	
		/* Decode Instruction */
		if (strcmp(instruction, "program") == 0)
			opcode = PROGRAM;
		else if (strcmp(instruction, "print") == 0)
			opcode = PRINT;
		else if (strcmp(instruction, "printl") == 0)
			opcode = PRINTL;
		else if (strcmp(instruction, "printh") == 0)
			opcode = PRINTH;
		else if (strcmp(instruction, "input") == 0)
			opcode = INPUT;
		else if (strcmp(instruction, "let") == 0)
			opcode = LET;
		else if (strcmp(instruction, "for") == 0)
			opcode = FOR;
		else if (strcmp(instruction, "next") == 0)
			opcode = NEXT;
		else if (strcmp(instruction, "goto") == 0)
			opcode = GOTO;
		else if (strcmp(instruction, "rem") == 0)
			opcode = REM;
		else
			opcode = END;
	}
	
	return opcode;
}

/* decode_l_number returns line number */
int decode_l_number(int l_number)
{
	int pcounter = 0;
	
	for(pcounter = 0; pcounter < instruction_counter; pcounter++)
		if(i_array[pcounter].l_number == l_number) {
			return pcounter - 1;
		}
	return 0;
}

/* decode_instruction returns 0 on END program */
int decode_instruction(char *buf)
{
	char *pch;

	/* Add Line Number */
	pch = strtok(buf, " ");
	i_array[instruction_counter].l_number = atoi(pch);
	
	/* Decode Instruction */
	pch = strtok(NULL, " ");
	i_array[instruction_counter].opcode = i_decode(pch);
	
	/* Return END Program */
	if (i_array[instruction_counter].opcode == END) {
		/* Update Instruction Counter */
		instruction_counter++;
		return PROGRAM_END;
	}

	/* Manage Instruction Buffer */
	pch = strtok(NULL, " ");
	str_terminate(pch);
	strcpy(i_array[instruction_counter].buffer, pch);

	/* Update Instruction Counter */
	instruction_counter++;

	return PROGRAM_ALIVE;
}

/* Execute Program */
int execute_instructions(void)
{
	int status = 0;
	int op_goto = 0;
	
	/* State Machine to execute the intructions */
	for(program_counter = 0; program_counter < instruction_counter;
		program_counter++) {
		switch (i_array[program_counter].opcode) {
			case PROGRAM:
			case REM:
			case END:
				break;
			case PRINT:
				status += opcode_print(
					i_array[program_counter].buffer);
				break;
			case PRINTL:
				status += opcode_printl(
					i_array[program_counter].buffer);
				break;
			case PRINTH:
				status += opcode_printh(
					i_array[program_counter].buffer);
				break;
			case INPUT:
				break;
			case LET:
				status += opcode_let(
					i_array[program_counter].buffer);
				break;
			case FOR:
				program_counter = opcode_for(
					program_counter,
					i_array[program_counter].buffer);
				break;
			case NEXT:
				program_counter = opcode_next(
					program_counter,
					i_array[program_counter].buffer);
				break;
			case GOTO:
				op_goto = opcode_goto(
					i_array[program_counter].buffer);
				program_counter = decode_l_number(op_goto);
				break;	
		}
	}

	printf("Execution: %d %d\n", program_counter, status);

	return status;
}

