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
*/

/*
 * @file main.cpp
 *
 *  Created on: 2004
 *      Author: Thomas Fischer
 */

#include <gtkmm/main.h>
#include "MainWindow.h"

int main (int argc, char **argv)
{
   Gtk::Main kit(argc, argv);

   MainWindow main_window;

   main_window.show ();

   Gtk::Main::run(main_window);

   return 0;
}
