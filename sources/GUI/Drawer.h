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
 * @file Drawer.h
 *
 *  Created on: 01/2005
 *      Author: Thomas Fischer
 */

#ifndef _DRAWER_H_
#define _DRAWER_H_

#include <gtkmm/window.h>
#include "Fractal.h"

class Drawer : public Gtk::Window
{
public:
   Drawer ();
   /// Constructor loads automaticaly parameters for Fractal
   // Drawer ( FractalConfig fc );
   virtual ~Drawer();

private:
   Glib::RefPtr <Gdk::Pixbuf> pixbuf;
   Gtk::VBox vbox;
   Gtk::MenuBar main_menu;

};

#endif	//_CANVAS_H
