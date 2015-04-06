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
#include "vhwmon-parameters.h"
#include "vhwmon-program.h"

/* Parameters definition */
#define FILENAME	-2
#define ERROR	-1
#define DEBUG	0
#define EXECUTE	1
#define USAGE	2
#define VERSION	3

static char program_name[256];

int decode_parameters(int *dargv, int argc, char *argv[])
{
	int i;
	int j = 0;

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0)
			dargv[j] = DEBUG;
		else if (strcmp(argv[i], "-e") == 0) {
			dargv[j] = EXECUTE;
			/* Eat the program_name parameter */
			i++;
			strcpy(program_name, argv[i]);
			j++;
			dargv[j] = FILENAME;
		} else if (strcmp(argv[i], "-u") == 0)
			dargv[j] = USAGE;
		else if (strcmp(argv[i], "-v") == 0)
			dargv[j] = VERSION;
		else
			dargv[j] = ERROR;
		
		j++;
	}

	return 0;
}

int execute_parameters(int *dargv, int argc, char *argv[])
{
	int i;
	int dindex = 0;
	
	int num_par = argc - 1;

	/* State Machine to analyze the parameters */
	for(dindex = 0; dindex < num_par; dindex++) {
		switch (dargv[dindex]) {
			case ERROR:
				printf("Usage: vhwmon [options] <filename>\n");
				printf("Options:\n");
				printf("-d\t\tDEBUG\n");
				printf("-e [filename]\tEXECUTE [filename]\n");
				printf("-v\t\tVERSION\n");
				printf("-u\t\tUSAGE\n");
				return 0;
			case DEBUG:
				printf("Numero di parametri: %d\n", argc);
				for (i = 1; i < argc; i++)
					printf("Parametro [%d] = %s\t%d\n",
							i, argv[i], dargv[i-1]);
				break;
			case EXECUTE:
				printf("Program file: %s\n", program_name);
				/* Eat the program_name parameter */
				num_par--;
				/* Execute Program File */
				execute_program(program_name);
				break;
			case USAGE:
				printf("Usage: vhwmon [options] <filename>\n");
				printf("Options:\n");
				printf("-d\t\tDEBUG\n");
				printf("-e [filename]\tEXECUTE [filename]\n");
				printf("-v\t\tVERSION\n");
				printf("-u\t\tUSAGE\n");
				break;
			case VERSION:
				printf("vhwmon vHardware Monitor 0.000\n");
				printf("Copyright(c) Vincenzo Frascino 2013\n");
				printf("Email: <gabrielknight4@gmail.com>\n");
				break;
		}
	}

	return 0;
}
