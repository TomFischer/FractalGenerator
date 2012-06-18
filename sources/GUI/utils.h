/*
* Copyright (C) 2004-2012 Thomas Fischer
*
* This file is part of "FractalGenerator". "FractalGenerator" is free
* software: you can redistribute it and/or modify it under the terms of
* the GNU General Public License as published by the Free Software Foundation,
* either version 3 of the License, or (at your option) any later version.
*
* "FractalGenerator" is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* "FractalGenerator". If not, see <http://www.gnu.org/licenses/>.
*
*/

/*
 * @file utils.h
 *
 *  Created on: 08/2004
 *      Author: Thomas Fischer
 */

#ifndef UTILS_H
#define UTILS_H

template<class T> void swap(T& arg0, T& arg1)
{
   T temp(arg0);
   arg0 = arg1;
   arg1 = temp;
}


#endif
