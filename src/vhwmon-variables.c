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

/* Integer 32bit Variable Structure */
struct variable
{
	/* max name longness */
	char name[32];
	/* value */
	int value;
};

/* Variable Array */
static struct variable v_array[128];

/* Variable Counter */
static int variable_counter = 0;

/* Add Variable */
void add_variable(char *name, int value)
{
	strncpy(v_array[variable_counter].name, name, 31);
	v_array[variable_counter].value = value;
	variable_counter++;
}

/* Update Variable */
void update_variable(char *name, int value)
{
	int v_index = 0;
	int found = 0;

	for (v_index = 0; v_index < variable_counter; v_index++)
		if (strcmp(v_array[v_index].name, name) == 0) {
			/* Variable Found */
			v_array[v_index].value = value;
			found = 1; 
		}

	if (found == 0)
		add_variable(name, value);
}

/* Find Variable */
int find_variable(char *name)
{
	int v_index = 0;
	
	for (v_index = 0; v_index < variable_counter; v_index++)
		if (strcmp(v_array[v_index].name, name) == 0)
			return v_array[v_index].value;
		else
			/* Variable Undeclared */
			add_variable(name, 0);
	
	
	return 0;
}

