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
#include "vhwmon-loops.h"
#include "vhwmon-debug.h"

/* Loop Structure */
struct loop {
	/* Loop Entry Point */
	int l_entry;
	/* Loop End Point */
	int l_end;
	/* Loop Validity */
	int l_validity;
};

/* 
 * Loop Array
 * Max 32 loop in a Program 
 */
static struct loop loops[32];
/* Loop Deepness */
static int deepness = 0;

/* Add Loop Entry Point */
int add_entry(int l_entry)
{
	int status = 0;

	/* Deepness verification */	
	if(deepness >= 32)
		status = -1;

	/* Update the Loop Entry Point */
	loops[deepness].l_entry = l_entry;
	deepness++;
	
	return status;
}

/* Add Loop End Point */
int add_end(int l_end)
{
	int status = 0;
	
	VHWMON_DEBUG("%d \n", deepness);
	
	/* Update the Loop Entry Point */
	if (deepness > 0) {
		deepness--;
		loops[deepness].l_end = l_end;
		loops[deepness].l_validity = 1;
		/* Update completed correctly */
		status = 1; 
	}
	
	return status;
}

/* Find Loop Entry Point */
int find_entry(int l_end)
{
	int l_entry = INVALID_LOOP;
	int i;
	
	for(i = 0; i <= deepness; i++) {
		if((loops[i].l_end == l_end) &&
			(loops[i].l_validity == 1))
			l_entry = loops[i].l_entry;
	}
	
	return l_entry;
}

/* Find Loop End Point */
int find_end(int l_entry)
{
	int l_end = INVALID_LOOP;
	int i;
	
	for(i = 0; i <= deepness; i++) {
		if((loops[i].l_entry == l_entry) &&
			(loops[i].l_validity == 1))
			l_end = loops[i].l_end;
	}
	
	return l_end;
}


