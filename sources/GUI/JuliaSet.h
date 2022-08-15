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
 * Die Klasse JuliaSet stellt eine Spezialisierung der Schnittstelle zur
 * Erstellung verschiedener Fraktale dar.
 */
class JuliaSet : public Fractal
{
public:
	/**
	 *
	 * @param p0 upper left point of image
	 * @param p1 lower right point of image
	 * @param c complex number/parameter of the quadratic polynomial iteration
	 * rule \f$z_{n+1} = z_{n}^2 + c\f$
	 * @param number_x_pix
	 * @param number_y_pix
	 * @param max_iterations
	 * @return
	 */
   JuliaSet (const Point2D &p0, const Point2D &p1, const Point2D &c,
              size_t number_x_pix, size_t number_y_pix, size_t max_iterations);
   ~JuliaSet ();

   /**
    * Sets the complex parameter of the quadratic polynomial iteration
    * rule \f$z_{n+1} = z_{n}^2 + c\f$
    * @param c the complex parameter
    */
   void setComplexParameter (Point2D const &c);
   /**
    * returns the complex parameter of the quadratic polynomial iteration
	 * rule \f$z_{n+1} = z_{n}^2 + c\f$
    * @return the complex parameter \f$c\f$
    */
   Point2D const& getComplexParameter () const { return _c; }

private:
   virtual void createFractal ();
   unsigned iteration (double zn[2]);
   Point2D _c;
};

#endif
