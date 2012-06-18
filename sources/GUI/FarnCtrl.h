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
 * @file FarnCtrl.h
 *
 *  Created on: 12/2004
 *      Author: Thomas Fischer
 */

#ifndef _FARNCTRL_H_
#define _FARNCTRL_H_

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/fileselection.h>

class Viewer;

class FarnCtrl : public Gtk::Window
{
public:
   FarnCtrl ();
   ~FarnCtrl ();

private:
   void onSaveDlg ();
   void onSave ();
   void onLoad ();
   void onOk ();
   void onClose ();

   Gtk::VBox vbox;
   Gtk::HButtonBox hbox;
   Gtk::Button save, load, ok, close;
   Viewer *viewer;
   Gtk::FileSelection *file_selection;
};
#endif	// _FARNCTRL_H_
