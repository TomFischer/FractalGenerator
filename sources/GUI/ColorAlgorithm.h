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
* Author: Thomas Fischer
*
*/

/*
 * @file ColorAlgorithm.h
 *
 *  Created on: 09/2004
 *      Author: Thomas Fischer
 */

#ifndef _COLORALGORITHM_H_
#define _COLORALGORITHM_H_

#include <gdkmm/color.h>

class ColorAlgorithm
{
public:
   ColorAlgorithm (size_t max_iter, Gdk::Color b_c_o, Gdk::Color b_c_t,
                   Gdk::Color p_c_o, Gdk::Color p_c_t, Gdk::Color o_c_o, Gdk::Color o_c_t);
   ~ColorAlgorithm();

   Gdk::Color getColor ( size_t iter ) const;

private:
   size_t max_iter;
   size_t bod_st_red, bod_st_green, bod_st_blue, per_st_red,
   per_st_green, per_st_blue, outer_st_red, outer_st_green,
   outer_st_blue;
   double bod_coeff_red, bod_coeff_green, bod_coeff_blue, per_coeff_red,
   per_coeff_green, per_coeff_blue, outer_coeff_red,
   outer_coeff_green, outer_coeff_blue;
};

#endif	//_COLORALGORITHM_H_
