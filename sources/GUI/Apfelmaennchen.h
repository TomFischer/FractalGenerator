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
*/

/*
 * @file Apfelmaennchen.h
 *
 *  Created on: 02/2005
 *      Author: Thomas Fischer
 */


#ifndef APFELMAENNCHEN_H
#define APFELMAENNCHEN_H

#include <cmath>
#include <vector>
#include "Fractal.h"
#include "Point.h"

/** \ingroup Fraktale
 */

/** Apfelmaennchen ist eine Spezialisierung der Klasse
 * Fractal und enth&auml;lt den Algorithmus zur Berechnung der
 * Mandelbrotmenge.
 *
 * Die Klasse Apfelmaennchen stellt eine Spezialisierung der Schnittstelle zur
 * Erstellung verschiedener Fraktale dar.
 */
class Apfelmaennchen : public Fractal
{
public:
   /** Zur Berechnung der Mandelbrotmenge ben&ouml;tigt der Algorithmus
    * folgende Daten
    * \param p0 linker unterer Punkt
    * \param p1 rechter oberer Punkt
    * \param number_x_pix Breite in Pixeln
    * \param number_y_pix H&ouml;he in Pixeln
    * \param max_iterations maximale Anzahl an Iterationen, bevor der
    * Ausgangspunkt als zur Mandelbrotmenge dazugeh&ouml;rig angenommen
    * wird.
    */
   Apfelmaennchen (const Point2D &p0, const Point2D &p1,
                   size_t number_x_pix, size_t number_y_pix, size_t max_iterations);
   /** Destruktor der Klasse
    */
   ~Apfelmaennchen ();

private:
   virtual void createFractal ();
   double normQuadrat (double a[2]);
   unsigned iteration (double zn[2]);
   unsigned iterationOptimized (double zn[2]);
   /** Feld speichert die letzten Iterationen um Perioden zu erkennen.
    * */
   const size_t field_size;
   std::vector <double> last_iterations;
   std::vector <double> last_iterations_imag;
};

#endif
