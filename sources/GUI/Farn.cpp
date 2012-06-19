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
 * Farn.cpp
 *
 *  Created on: 02/2005
 *      Author: Thomas Fischer
 */


#include <cstdlib>
#include "Farn.h"

Farn::Farn ( size_t width, size_t height,
		Point2D p0, Point2D p1 )
      : Fractal ( p0, p1, height, width, 100, std::string ("Farn") ),
      a (4), b(4), c(4), d(4), e(4), f(4), p(4)
{
   /*
   Winkelreihenfolge entspricht Index im vector
   \alpha = 0	\alpha = 49		\alpha = -50	\alpha = -2.5
   */
   // a[i]  k_x \cdot \cos (\alpha)
   a[0] = 0.00;
   a[1] =  0.197;
   a[2] = -0.193;
   a[3] =  0.849;
   // b[i]  -k_y \cdot \sin (\alpha)
   b[0] = 0.00;
   b[1] = -0.226;
   b[2] =  0.283;
   b[3] =  0.037;
   // c[i]  k_x \cdot \sin (\alpha)
   c[0] = 0.00;
   c[1] =  0.226;
   c[2] =  0.230;
   c[3] = -0.037;
   // d[i]  k_y \cdot \cos (\alpha)
   d[0] = 0.16;
   d[1] =  0.197;
   d[2] =  0.238;
   d[3] =  0.849;
   // e, f Verschiebungen in x bzw. y Richtung
   e[0] = 0.00;
   e[1] =  0.000;
   e[2] =  0.000;
   e[3] =  0.000;
   f[0] = 0.00;
   f[1] =  0.160;
   f[2] =  0.044;
   f[3] =  0.160;
   // Wahrscheinlichkeit eine der vier Operationen auszuführen ???
   p[0] = 0.01;
   p[1] =  0.070;
   p[2] =  0.070;
   p[3] =  0.850;

   createFractal ();
}

Farn::~Farn ()
{}

void Farn::createFractal ( )
{
   double x = 0.0, y = 0.0, summe, xneu, yneu;
   double xmin = p0[0], ymin = p0[1];
   double xmax = p1[0], ymax = p1[1];
   size_t k, xs, ys;
   long l;
   size_t dx = getRows (), dy = getCols ();

   for (xs = 0; xs < dx; ++xs)
      for (ys = 0; ys < dy; ++ys)
         matrix (xs, ys) = 0;

   for (l=0; l<150000; ++l) {
      k = 0;
      summe = p[0];
      while (summe < random ()) {
         ++k;
         summe += p[k];
      }
      xneu = a[k] * x + b[k] * y + e[k];
      yneu = c[k] * x + d[k] * y + f[k];
      x = xneu;
      y = yneu;
      xs = size_t (dx * (x - xmin) / (xmax - xmin));
      ys = size_t (dy * (ymax - y) / (ymax - ymin));


      matrix (ys, xs) = k*20;
   }
}
