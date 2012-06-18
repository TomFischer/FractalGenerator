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
 * @file ColorDlg.h
 *
 *  Created on: 09/2004
 *      Author: Thomas Fischer
 */

#ifndef _COLORDLG_H_
#define _COLORDLG_H_

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <string>

#include "ColorGradientSelection.h"

class ColorDlg : public Gtk::VBox
{
public:
   ColorDlg ();
   ~ColorDlg ();

   // ColorDlg interface
   void onOk ();
   void getColors (Gdk::Color &body_col_one, Gdk::Color &body_col_two,
                   Gdk::Color &per_col_one, Gdk::Color &per_col_two,
                   Gdk::Color &out_col_one, Gdk::Color &out_col_two);
   void getColors ( std::vector <Gdk::Color> &colors );
   void showDlg ( std::string button_name );
   void setColors ( std::vector <Gdk::Color> &colors );
   // TODO: add member function declarations...

private:
   Gtk::Label label;
   Gtk::Button button_body, button_peripherie, button_outer;
   ColorGradientSelection body_sel, peripherie_sel, outer_sel;
};


#endif	//_COLORDLG_H_
