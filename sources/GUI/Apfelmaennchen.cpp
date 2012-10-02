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
 * @file Apfelmaennchen.cpp
 *
 *  Created on: 02/2005
 *      Author: Thomas Fischer
 */

#include "Apfelmaennchen.h"
#include <exception>
#include <stdexcept>
#include <iostream>

Apfelmaennchen::Apfelmaennchen (const Point2D &p0, const Point2D &p1,
		size_t number_x_pix, size_t number_y_pix, size_t max_iterations)
      : Fractal ( p0, p1, number_x_pix, number_y_pix,
                  max_iterations, std::string ("Mandelbrotmenge") ),
      field_size (10),
      last_iterations (field_size),
      last_iterations_imag (field_size)

{
   createFractal ();
}

Apfelmaennchen::~Apfelmaennchen ()
{}

// momentan stuerzt Algorithmus ab bei folgenden Parametern
// p0 ( -1.78, 0.03 ) p1 ( -1.72, 0.03 ) size 950
void Apfelmaennchen::createFractal ( )
{
   size_t i0, i1;
   double c[2];

   size_t maxx_pix = matrix.getRows ();
   size_t maxy_pix = matrix.getCols ();

   double x0 = _p0[0];
   double x1 = _p1[0];
   double dx = (x1 - x0) / maxx_pix;

   double y0 = _p0[1];
   double y1 = _p1[1];
   double dy = (y1 - y0) / maxy_pix;

   if ((y0 < 0) & (y1 > 0)) {
      size_t sym_idx = size_t(fabs (y0) / dy);
      if (fabs(y0) < fabs (y1)) {
         // rechts steht was ueber
         for (i0 = 0; i0 < maxx_pix; i0++) {
            for (i1 = sym_idx; i1 < maxy_pix; i1++) {
               c[0] = x0 + i0 * dx;
               c[1] = y0 + i1 * dy;
               matrix (i0, i1) = iteration (c);
            }
         }
         for (i0 = 0; i0 < maxx_pix; i0++) {
            for (i1 = sym_idx + 1; i1 > 0; i1--) {
               matrix (i0, i1) = matrix (i0, 2 * sym_idx - i1 + 1);
            }
         }
      } else {
         // links steht was ueber oder es herrscht "pure" Symmetrie
         for (i0 = 0; i0 < maxx_pix; i0++) {
            for (i1 = 0; i1 <= sym_idx + 1; i1++) {
               c[0] = x0 + i0 * dx;
               c[1] = y0 + i1 * dy;
               matrix (i0, i1) = iteration (c);
            }
         }
         for (i0 = 0; i0 < maxx_pix; i0++) {
            for (i1 = sym_idx; i1 < maxy_pix; i1++) {
               try {
                  matrix (i0, i1) = matrix (i0, 2 * sym_idx + 1 - i1);
               } catch (std::range_error &re) {
                  std::cout << "ERROR " << re.what () << '\t';
               }
            }
         }
      }
   } else {
      // keine Symmetrie
      for (i0 = 0; i0 < maxx_pix; i0++) {
         for (i1 = 0; i1 < maxy_pix; i1++) {
            c[0] = x0 + i0 * dx;
            c[1] = y0 + i1 * dy;
            matrix (i0, i1) = iteration (c);
         }
      }
   }
}

unsigned Apfelmaennchen::iteration (double c[2])
{
   double zn[2];

   // Startpunkt fuer Iteration fest
   zn[0] = 0.0;
   zn[1] = 0.0;

   size_t i, res = getMaxIterations ();
   for (i = 0; (i < res) && (normQuadrat(zn) < 4.0); ++i) {
      if (normQuadrat (zn) < 4.0) {
         // z_{n+1} = z_n^2 + c
         double real = zn[0] * zn[0] - zn[1] * zn[1] + c[0];
         double imag = 2 * zn[0] * zn[1] + c[1];

         zn[0] = real;
         zn[1] = imag;
      } else {
         break;
      }
   }

   return i;
}

unsigned Apfelmaennchen::iterationOptimized (double c[2])
{
   double zn[2];
   double my_eps = 1e-7;

   // Startpunkt fuer Iteration fest
   zn[0] = 0.0;
   zn[1] = 0.0;

   // zu Beginn jeder Iteration initialisieren
   for (size_t i=0; i<field_size; ++i) {
      last_iterations[i] = 0.0;
      last_iterations_imag[i] = 0.0;
   }

   size_t i, res = getMaxIterations ();
   for (i = 0; (i < res) & (normQuadrat(zn) < 4.0); ++i) {
      if (normQuadrat (zn) < 4.0) {
         // z_{n+1} = z_n^2 + c
         double real = zn[0] * zn[0] - zn[1] * zn[1] + c[0];
         double imag = 2 * zn[0] * zn[1] + c[1];
         // Test auf Periode
         for (size_t j = 0; j < field_size; ++j) {
            double dist = pow ( real - last_iterations[j], 2);
            dist += pow ( imag - last_iterations_imag[j], 2);
            if (dist < my_eps)
               //return i;
               return res;
         }
         // abspeichern an entsprechender Position
         last_iterations[i % field_size] = real;

         zn[0] = real;
         zn[1] = imag;
      } else {
         return i;
      }
   }

   return i;
}

double Apfelmaennchen::normQuadrat ( double a[2] )
{
   return (a[0] * a[0] + a[1] * a[1]);
}
