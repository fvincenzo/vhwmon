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
#ifndef VHWMON_PARAMETERS_H_INCLUDED
#define VHWMON_PARAMETERS_H_INCLUDED

int decode_parameters(int *dargv, int argc, char *argv[]);
int execute_parameters(int *dargv, int argc, char *argv[]);

#endif /* VHWMON_PARAMETERS_H_INCLUDED */
