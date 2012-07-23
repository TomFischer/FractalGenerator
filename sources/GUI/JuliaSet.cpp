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
 * @file JuliaSet.cpp
 *
 *  Created on: 02/2005
 *      Author: Thomas Fischer
 */

#include "JuliaSet.h"

double fpow (double x, unsigned p)
{
   if (p==0) return 1.0;
   else return x*fpow(x, p-1);
}

JuliaSet::JuliaSet (const Point2D &p0, const Point2D &p1,
                    size_t number_x_pix, size_t number_y_pix, size_t max_iterations)
      : Fractal ( p0, p1, number_x_pix, number_y_pix, max_iterations, std::string ("Julia Set") ),
        _c()
{
   // complex number c
//	_c[0] = 1.25; _c[1] = 0.0;
	_c[0] = 0.0; _c[1] = 1.25;
//	_c[0] = -0.8; _c[1] = 0.2;
   //c[0] = 0.285; c[1] = 0.013;
   //c[0] = -1.0; c[1] = 1.0;
   //c[0] = -1.0; c[1] = 0.0;
   //c[0] = 0.70365; c[1] = 0.2301;

   createFractal ();
}

JuliaSet::~JuliaSet ()
{}

void JuliaSet::setStartPoint(Point2D const& c)
{
	_c = c;
	createFractal();
}

void JuliaSet::createFractal ( )
{
   const size_t maxx_pix (matrix.getRows ());
   const size_t maxy_pix (matrix.getCols ());

   const double dx ((p1[0] - p0[0]) / maxx_pix);
   const double dy ((p1[1] - p0[1]) / maxy_pix);

   for (size_t i0 = 0; i0 < maxx_pix; i0++) {
      for (size_t i1 = 0; i1 < maxy_pix; i1++) {
         double zn[2] = {p0[0] + i0 * dx, p0[1] + i1 * dy};
         matrix (i0, i1) = iteration (zn);
      }
   }
}

/*
unsigned JuliaSet::iteration (double zn[2])
{
   size_t i, max_it (getMaxIterations ());
	 double nrm2 (0.0);
   for (i = 0; (i < max_it) && (nrm2<4.0); ++i) {
      if (nrm2 < 4.0) {

         // z_{n+1} = z_n^7 + c
         double real = fpow(zn[0],7)-21*fpow(zn[0],5)*fpow(zn[1],2)+35*fpow(zn[0],3)*fpow(zn[1],4)-7*zn[0]*fpow(zn[1],6) + c[0];
         double imag = 7*fpow(zn[0],6)*zn[1]-35*fpow(zn[0],4)*fpow(zn[1],3)+21*zn[0]*fpow(zn[1],6) + c[1];


         // z_{n+1} = z_n^6 + c
         double real = fpow(zn[0],6)-15*fpow(zn[0],4)*fpow(zn[1],2)+15*fpow(zn[0],2)*fpow(zn[1],4) - fpow(zn[1],6) + c[0];
         double imag = 6*fpow(zn[0],5)*zn[1]-20*fpow(zn[0],3)*fpow(zn[1],3)+6*zn[0]*fpow(zn[1],5) + c[1];

         // z_{n+1} = z_n^5 + c
         double real = fpow(zn[0],5)-10*fpow(zn[0],3)*fpow(zn[1],2)+5*zn[0]*fpow(zn[1],4) + c[0];
         double imag = 5*fpow(zn[0],4)*zn[1]-10*fpow(zn[0],2)*fpow(zn[1],3)+fpow(zn[1],5) + c[1];

         zn[0] = real;
         zn[1] = imag;
				 nrm2 = zn[0]*zn[0]+zn[1]*zn[1];
      } else {
         break;
      }
   }

   return i;
}
*/

/*
unsigned JuliaSet::iteration (double zn[2])
{
   size_t i, max_it = getMaxIterations ();
	 double nrm2 (0.0);
   for (i = 0; (i < max_it) && (nrm2 < 4.0); ++i) {
      // z_{n+1} = z_n^3 + c
      double real = zn[0]*zn[0]*zn[0] - 3*zn[0]*zn[1]*zn[1] + c[0];
      double imag = 3*zn[0]*zn[0]*zn[1] - zn[1]*zn[1]*zn[1] + c[1];

      zn[0] = real;
      zn[1] = imag;
      nrm2 = zn[0]*zn[0]+zn[1]*zn[1];
   }
   return i;
}
*/

unsigned JuliaSet::iteration (double zn[2])
{
   size_t i, max_it (getMaxIterations ());
   double nrm2 (0.0);
   for (i = 0; (i < max_it) && (nrm2 < 4.0); ++i) {
      // z_{n+1} = z_n^2 + c
      double real = zn[0] * zn[0] - zn[1] * zn[1] + _c[0];
      double imag = 2 * zn[0] * zn[1] + _c[1];

      zn[0] = real;
      zn[1] = imag;
      nrm2 = zn[0]*zn[0]+zn[1]*zn[1];
   }

   return i;
}
