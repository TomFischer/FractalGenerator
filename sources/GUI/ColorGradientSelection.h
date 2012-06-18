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
 * @file ColorGradientSelection.h
 *
 *  Created on: 09/2004
 *      Author: Thomas Fischer
 */

#ifndef _COLORGRADIENTSELECTION_H_
#define _COLORGRADIENTSELECTION_H_

#include <gtkmm/window.h>
#include <gtkmm/colorselection.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/button.h>
#include <gtkmm/separator.h>

class ColorGradientSelection : public Gtk::Window
{
public:
   ColorGradientSelection();
   ~ColorGradientSelection();

   Gdk::Color getFirstColor () const;
   Gdk::Color getSecondColor () const;
   void setFirstColor ( Gdk::Color &color );
   void setSecondColor ( Gdk::Color &color );
   void onOk ();
   void onCancel ();


private:
   Gtk::VBox vbox;
   Gtk::ColorSelection first_selection, second_selection;
   Gtk::HSeparator hsep0, hsep1;
   Gtk::HButtonBox button_box;
   Gtk::Button ok, cancel;
};


#endif	//_COLORGRADIENTSELECTION_H_
