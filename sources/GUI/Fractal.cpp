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
 * @file Fractal.cpp
 *
 *  Created on: 2004
 *      Author: Thomas Fischer
 */

#include "Fractal.h"

Fractal::Fractal ( const Point2D &ap0, const Point2D &ap1,
               size_t number_x_pix, size_t number_y_pix, size_t amax_iterations,
               const std::string &name )
      : matrix (number_y_pix, number_x_pix),
      _p0 (ap0), _p1 (ap1), fractal_name (name), max_iterations (amax_iterations)
{}

Fractal::~Fractal ()
{}

const unsigned Fractal::operator() (size_t row, size_t col) const
{
   return matrix(row, col);
}

size_t* Fractal::getData () const
{
   size_t rows = getRows ();
   size_t cols = getCols ();
   size_t* data = new size_t [ rows * cols ];

   for (size_t i = 0; i < rows; ++i)
      for (size_t j = 0; j < cols; ++j)
         data[i * cols + j] = matrix (i, j);

   return data;
}

size_t Fractal::getMaxVal () const
{
	size_t rows (getRows ());
	size_t cols (getCols ());
	size_t max (matrix(0,0));

	for (size_t r(0); r<rows; ++r) {
		for (size_t c(0); c<cols; ++c) {
			if (matrix(r,c) > max) max = matrix (r,c);
		}
	}

	return max;
}

size_t Fractal::getMinVal () const
{
	size_t rows (getRows ());
	size_t cols (getCols ());
	size_t min (matrix(0,0));

	for (size_t r(0); r<rows; ++r) {
		for (size_t c(0); c<cols; ++c) {
			if (matrix(r,c) < min) min = matrix (r,c);
		}
	}

	return min;
}

