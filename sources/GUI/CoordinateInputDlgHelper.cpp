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
 * @file CoordinateInputDlgHelper.cpp
 *
 *  Created on: 03/2005
 *      Author: Thomas Fischer
 */

#include "CoordinateInputDlgHelper.h"
#include <iostream>
#include <cstdio>

CoordinateInputDlgHelper::CoordinateInputDlgHelper ()
      : Gtk::HBox (), coordinate_label (), spin_button (0.00001, 6)
{
   coordinate_label.set_text ("x");
   add (coordinate_label);

   spin_button.set_range (-2.0, 2.0);
   spin_button.set_value (0.0);
   spin_button.set_increments (0.00001, 0.001);
   add (spin_button);
}

CoordinateInputDlgHelper::CoordinateInputDlgHelper (
   const CoordinateInputDlgHelper& src)
      : Gtk::HBox (), coordinate_label (), spin_button (0.00001, 6)
{
   coordinate_label.set_text ("x");
   add (coordinate_label);

   spin_button.set_range (-2.0, 2.0);
   spin_button.set_value (0.0);
   spin_button.set_increments (0.00001, 0.001);
   add (spin_button);
}

CoordinateInputDlgHelper::CoordinateInputDlgHelper ( size_t dim,
      double def_value, double min, double max )
      : Gtk::HBox (), coordinate_label (), spin_button (0.00001, 6)
{
   std::cout << "CoordinateInputDlgHelper::CoordinateInputDlgHelper user";
   std::cout << std::endl;
   if (dim == 0)
      coordinate_label.set_text ("0");
   if (dim == 1)
      coordinate_label.set_text ("1");
   if (dim == 2)
      coordinate_label.set_text ("2");
   if (dim == 3)
      coordinate_label.set_text ("3");
   add (coordinate_label);

   spin_button.set_range (min, max);
   spin_button.set_value (def_value);
   spin_button.set_increments (0.000001, 0.0001);
   add (spin_button);
}

double CoordinateInputDlgHelper::getCoordinate () const
{
   return spin_button.get_value ();
}

void CoordinateInputDlgHelper::setCoordinate ( double value )
{
   spin_button.set_value ( value );
}

Gtk::SpinButton& CoordinateInputDlgHelper::getSpinButton ()
{
   return spin_button;
}

void CoordinateInputDlgHelper::setLabel ( const std::string label )
{
   coordinate_label.set_text (label.c_str ());
}
