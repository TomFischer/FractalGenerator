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
 * @file Fractal.h
 *
 *  Created on: 2004
 *      Author: Thomas Fischer
 */
#ifndef FRACTAL_H
#define FRACTAL_H

#include <string>

#include "matrix.h"
#include "Point.h"

/** \defgroup Fraktale
 */

/** \ingroup Fraktale
 */

/** Fractal ist die Basisklasse aller Fraktale wie
 * Apfelmaennchen, JuliaSet, Farn.
 *
 * Die Klasse Fraktal stellt eine allgemeine Schnittstelle zur
 * Erstellung verschiedener Fraktale dar.
 */
class Fractal
{
public:
   /** Destruktor der Klasse
    */
   virtual ~Fractal ();
   unsigned operator() (size_t row, size_t col) const;
   unsigned getMaxIterations () const {
      return max_iterations;
   }
   size_t getRows () const {
      return matrix.getRows ();
   }
   size_t getCols () const {
      return matrix.getCols ();
   }
   const std::string& getName () const {
      return fractal_name;
   }
   const Point2D& getUpperLeftPoint() const {
      return _p0;
   }
   const Point2D& getLowerRightPoint () const {
      return _p1;
   }
   size_t* getData () const;

	 size_t getMaxVal() const;
	 size_t getMinVal() const;

protected:
   /** Fractal Konstruktor.
    *
    * Die zweidimensionale Zeichenfl&auml;che wird durch die beiden
    * Punkte p0 und p1 bestimmt.
    * \param p0 vom Typ \class Point speichert die Koordinaten des unteren
    * linken Punktes
    * \param p1 vom Typ \class Point speichert die Koordinaten des oberen
    * rechten Punktes
    * \param number_x_pix die Breite des Fraktals
    * \param number_y_pix die H&ouml;he des Fraktals
    * \param max_iterations maximale Anzahl der Iterationen
    * \param name Name des Fraktals
    */
   Fractal ( const Point2D &p0, const Point2D &p1,
             size_t number_x_pix, size_t number_y_pix,
             size_t max_iterations, const std::string &name );
   /** matrix enth&auml;lt die einzelnen Iterationen der Ausgangspunkte
    * der gerasterten Fl&auml;che.
    */
   Matrix <size_t> matrix;
	/**
	 * upper left point
	 */
   Point2D _p0;
   Point2D _p1;
   std::string fractal_name;

private:
   size_t max_iterations;
};

#endif
