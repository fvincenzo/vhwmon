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

#define PROGRAM_MAX_LINES	256

static int program_dim;

int verify_program(char *buf, char *prog_name)
{
	char *pch = NULL;
	int program_ok = 0;
	
	if(buf != NULL)
		pch = strtok(buf, " ");
	
	while(pch != NULL) {
		if (strcmp(pch, "PROGRAM") == 0) {
			program_ok = 1;
			break;
		}
		pch = strtok(NULL, " ");
	}
	
	if (program_ok) {
		/* Read Program Name */
		pch = strtok(NULL, " ");

		/* Convert Program Name to Lower Case */
		str_terminate(pch);
		str_tolower(pch);
		str_tolower(prog_name);
		
		/* Verify that the program and file name are the same */
		if(strcmp(prog_name, pch) != 0) {
			printf("Error: Program and file name must be the same!\n");
			exit(1);
		}
	} else {
		printf("Error: the first line of the program must contain\n");
		printf("PROGRAM statement followed by program name\n");
		exit(1);
	}
	return 0;
}

int execute_program(char *program_name)
{
	FILE *fd;
	char buf[200];
	char cbuf[200];
	char *res;
	int end_program = 1;
	int program_status = 0;


	/* Opening Program File */
	fd=fopen(program_name, "r+");
	if( fd==NULL ) {
		printf("Error opening file: %s\n", program_name);
		return 0;
	}


	/* Read and Execute Program Line */
	while((program_dim < PROGRAM_MAX_LINES) && end_program) {
		res=fgets(buf, 200, fd);
		if(res == NULL)
			break;
		
		if(program_dim == 0) {
			strcpy(cbuf, buf);
			verify_program(cbuf, program_name);
		}
					
		end_program = decode_instruction(buf);
	
		program_dim++;
	}

	/* Close Program file */
	fclose(fd);

	/* Execute Program */
	program_status = execute_instructions();

	return program_status;
}

void init_program(void)
{
	program_dim = 0;
}
