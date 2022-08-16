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
 * ApfelmaennchenWidget.h
 *
 *  Created on: 02/2005
 *      Author: Thomas Fischer
 */

#ifndef APFELMAENNCHENWIDGET_H_
#define APFELMAENNCHENWIDGET_H_

#include <gtkmm/box.h>
#include <gtkmm/table.h>
#include <gtkmm/scale.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/separator.h>
#include <gtkmm/buttonbox.h>

#include "Apfelmaennchen.h"
#include "PointInputDlg.h"
#include "Point.h"

class ViewerWidget;

/**  ApfelmaennchenWidget beinhaltet die Widgets f&uuml;r
 * 	 Einstellungensm&ouml;glichkeiten des Fraktals
 * 	 Apfelmaennchen und zeigt diese an.
 */
class ApfelmaennchenWidget : public Gtk::VBox
{
public:
   /// Konstruktor erstellt alle Widgets und ordnet diese innerhalb einer
   /// Gtk::VBox an
   ///
   ApfelmaennchenWidget ( ViewerWidget &viewer_widget);
   virtual ~ApfelmaennchenWidget();

   Point2D getPoint (size_t num) const;
   size_t getIterationDepth () const;
   size_t getSize () const;
   void actualizePointerPosition ( int x, int y );
   PointInputDlg& getPointInputDlg ( unsigned point );
   void onCoordinateChanged ( unsigned dim, unsigned x, unsigned y );
   void update ();

private:
   guint8* getData ();
   ViewerWidget &viewer_widget;
   Gtk::VBox geometry_box;
   PointInputDlg left_lower_input_dlg, right_upper_input_dlg;
   Gtk::Label iteration_depth;
   Gtk::Label size;
   Gtk::HScale res_slider;
   Gtk::HScale size_slider;
   Gtk::HBox mouse_box, num_iter_box;
   Gtk::Label mouse_pos_x, mouse_pos_y, num_iter_label;
   Gtk::Image overview_img;
   Gtk::Table btn_table;
   Gtk::Button apply_btn, new_btn, save_btn, movie_btn;
   Gtk::HSeparator hsep0;
};

#endif	//APFELMAENNCHENWIDGET_H
