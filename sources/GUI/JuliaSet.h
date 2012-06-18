/*
* Copyright (C) 2005-2012 Thomas Fischer
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
 * @file JuliaSet.h
 *
 *  Created on: 02/2005
 *      Author: Thomas Fischer
 */

#ifndef JULIASET_H
#define JULIASET_H

#include <cmath>
#include "Fractal.h"
#include "Point.h"

/** \ingroup Fraktale
 */

/** JuliaSet ist eine Spezialisierung der Klasse
 * Fractal und enth&auml;lt den Algorithmus zur Berechnung der
 * Juliamenge.
 *
 * Die Klasse JuliaMenge stellt eine Spezialisierung der Schnittstelle zur
 * Erstellung verschiedener Fraktale dar.
 */
class JuliaSet : public Fractal
{
public:
   JuliaSet (const Point2D &p0, const Point2D &p1,
              size_t number_x_pix, size_t number_y_pix, size_t max_iterations);
   ~JuliaSet ();
   void setStartPoint (double x, double y);

private:
   virtual void createFractal ();
   unsigned iteration (double zn[2]);
   double *c;
};

#endif
