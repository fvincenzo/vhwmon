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
#include "vhwmon-parameters.h"
#include "vhwmon-program.h"

int main(int argc, char *argv[])
{
	/* Decoded instructions */
	int dargv[10];


	if (argc < 2 || argc > 9) {
		printf("Usage: vhwmon [options] <filename>\n");
		printf("Options:\n");
		printf("-d\t\tDEBUG\n");
		printf("-e [filename]\tEXECUTE [filename]\n");
		printf("-v\t\tVERSION\n");
		printf("-u\t\tUSAGE\n");
		return 0;
	}

	/* Init Program */
	init_program();

	/* Decode Parameters */
	decode_parameters(dargv, argc, argv);
	
	/* Execute Parameters */
	execute_parameters(dargv, argc, argv);
	
	return 0;
}


