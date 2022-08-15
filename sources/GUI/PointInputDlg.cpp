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
 * @file PointInputDlg.cpp
 *
 *  Created on: 08/2004
 *      Author: Thomas Fischer
 */

#include "PointInputDlg.h"
#include <iostream>
#include <cstdio>
#include "lexical_cast.h"

PointInputDlg::PointInputDlg ( size_t dim, double *limits )
      : Gtk::VBox (), coordinates (dim), label ()
{
   std::cout << std::endl;

   for (size_t i=0; i<coordinates.size (); ++i) {
      std::string coordinate_label = lexical_cast <std::string> (i);
      coordinates[i].setLabel ( coordinate_label );
      add (coordinates[i]);
   }

   label.set_text ("point ");
   add (label);
}

PointInputDlg::PointInputDlg ()
      : Gtk::VBox (), coordinates (2), label ()
{
   std::cout << std::endl;

   label.set_text ("point");
   add (label);

   for (size_t i=0; i<coordinates.size (); ++i) {
      std::string coordinate_label = lexical_cast <std::string> (i);
      coordinates[i].setLabel ( coordinate_label );
      add (coordinates[i]);
   }
}

PointInputDlg::~PointInputDlg ()
{}

double PointInputDlg::getCoordinate (size_t dim) const
{
    if (dim < coordinates.size())
        return coordinates[dim].getCoordinate();
    else
        throw std::range_error(
            "CoordinateInputDlg::getCoordinate falsche Dimension");
}

void PointInputDlg::setCoordinate(size_t dim, double value)
{
   if (dim < coordinates.size ())
      return coordinates[dim].setCoordinate ( value );
   else
      throw std::range_error
      ("CoordinateInputDlg::getCoordinate falsche Dimension");
}

void PointInputDlg::setNameOfPoint(std::string const& name)
{
   label.set_text ( name.c_str () );
}
