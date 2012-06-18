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
 * JuliaSetWidget.cpp
 *
 *  Created on: 02/2005
 *      Author: Thomas Fischer
 */

#ifndef FARN_H
#define FARN_H

#include <cmath>
#include <vector>
#include "Fractal.h"
#include "Point.h"

/** \ingroup Fraktale
 */

/** Farn ist eine Spezialisierung der Klasse
 * Fractal und enth&auml;lt den Algorithmus zur Berechnung des Barnsley-Farns.
 *
 * Die Klasse Farn stellt eine Spezialisierung der Schnittstelle zur
 * Erstellung verschiedener Fraktale dar.
 */
class Farn : public Fractal
{
public:
   Farn (size_t x, size_t y, Point2D p0, Point2D p1);
   ~Farn ();

private:
   double random () {
      return double (rand ()) / RAND_MAX;
   }
   virtual void createFractal ();
   std::vector <double> a, b, c, d, e, f, p;
};

#endif
