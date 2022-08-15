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
* @file PointInputDlg.h
*
*  Created on: 08/2004 by Thomas Fischer
*/

#ifndef _POINTINPUTDLG_H_
#define _POINTINPUTDLG_H_

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include "CoordinateInputDlgHelper.h"
#include <exception>
#include <stdexcept>

/// class PointInputDlg erm&ouml;glicht die Eingabe von Koordinaten
/// eines Punktes
class PointInputDlg : public Gtk::VBox
{
public:
   PointInputDlg ( size_t dim, double *limits );
   /// Standardkonstruktor: setzt dim auf 2 und limits auf -2.0 .. 2.0
   PointInputDlg ();
   ~PointInputDlg();

   double getCoordinate(size_t dim) const;
   void setCoordinate(size_t dim, double value);
   void setNameOfPoint ( std::string const& name );

protected:

private:
   std::vector<CoordinateInputDlgHelper> coordinates;
   Gtk::Label label;
};

#endif	// _POINTINPUTDLG_H_
