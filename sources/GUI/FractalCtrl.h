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
 * @file FractalCtrl.h
 *
 *  Created on: 01/2005
 *      Author: Thomas Fischer
 */

#ifndef _FRACTALCTRL_H_
#define _FRACTALCTRL_H_

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/fileselection.h>
#include <list>

#include "ApfelMaennchenCtrl.h"

class Fractal;
class Viewer;
class MainWindow;

/// class FractalCtrl vereint allgemeine Eigenschaften aller FractalCtrls
class FractalCtrl : public Gtk::Window
{
public:
   FractalCtrl ( MainWindow *parent, ApfelMaennchenCtrl *pluged_ctrl );
   ~FractalCtrl();

private: // Methods
   void onSaveDlg ();
   void onSave ();
   void onLoadDlg ();
   void onLoad ();
   void onClose ();
   void onOk ();
   guint8* getData (const ColorAlgorithm &alg);
   guint8* getData ();

protected: // Attributes
   // Gtk::FileChooser *file_chooser;
   Gtk::FileSelection *file_chooser;
   Gtk::VBox vbox;
   Gtk::HButtonBox hbox;
   Gtk::Button save, load, ok, close;
   std::list <Fractal *> fractal_list;
   std::list <Fractal *>::iterator fractal_bm;
   ApfelMaennchenCtrl *pluged_ctrl;
   Viewer *viewer;
   MainWindow *parent;
   Glib::RefPtr < Gdk::Pixbuf > pixbuf, own_color_pixbuf;
};

#endif	//_FRACTALCTRL_H_
