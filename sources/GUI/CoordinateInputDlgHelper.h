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
 * @file CoordinateInputDlgHelper.h
 *
 *  Created on: 03/2005
 *      Author: Thomas Fischer
 */

#ifndef _COORDINATEINPUTDLGHELPER_H_
#define _COORDINATEINPUTDLGHELPER_H_

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/spinbutton.h>

/// class CoordinateInputDlgHelper erm&ouml;glicht die Eingabe einer Koordinate
class CoordinateInputDlgHelper : public Gtk::HBox
{
public:
   CoordinateInputDlgHelper (size_t dim, double def_value,
                             double min, double max);
   /// default Konstruktor - wird mindestens f&uuml;r Vektoren / Felder
   /// ben&ouml;tigt
   CoordinateInputDlgHelper ();
   /// Copy-Konstruktor
   CoordinateInputDlgHelper ( const CoordinateInputDlgHelper& src);
   /// getCoordinate liefert den Wert der Koordinate zur&uuml;ck
   double getCoordinate () const;
   void setCoordinate ( double value );
   Gtk::SpinButton& getSpinButton ();
   void setLabel ( const std::string label);

private:
   Gtk::Label coordinate_label;
   Gtk::SpinButton spin_button;
};

#endif	//_COORDINATEINPUTDLGHELPER_H_
