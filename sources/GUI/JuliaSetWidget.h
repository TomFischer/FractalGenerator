/*
* Copyright (C) 2008-2012 Thomas Fischer
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
 * @file JuliaSetWidget.h
 *
 *  Created on: 02/2008
 *      Author: Thomas Fischer
 */

#ifndef JULIASETWIDGET_H_
#define JULIASETWIDGET_H_

#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include <gtkmm/scale.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/separator.h>

#include "JuliaSet.h"
#include "PointInputDlg.h"
#include "Point.h"

class ViewerWidget;

/**  JuliaSetWidget beinhaltet die Widgets f&uuml;r
 * 	 Einstellungensm&ouml;glichkeiten des Fraktals
 * 	 JuliaSet und zeigt diese an.
 */
class JuliaSetWidget : public Gtk::VBox
{
public:
   /// Konstruktor erstellt alle Widgets und ordnet diese innerhalb einer
   /// Gtk::VBox an
   ///
   JuliaSetWidget (ViewerWidget &viewer_widget);
   virtual ~JuliaSetWidget();

   size_t getIterationDepth() const;
   size_t getSize() const;
   void actualizePointerPosition ( int x, int y );
   Point2D getComplexParameter() const;
   Point2D getUpperLeftPoint() const;
   Point2D getLowerRightPoint() const;
   void onCoordinateChanged ( unsigned dim, unsigned x, unsigned y );

private:
//   guint8* getData ();
   ViewerWidget &viewer_widget;
   Gtk::Frame _geometric_properties_frame;
   Gtk::VBox _geometry_box;
   PointInputDlg _complex_parameter_input_dlg;
   PointInputDlg _upper_left_point_input_dlg;
   PointInputDlg _lower_right_point_input_dlg;
   Gtk::Label iteration_depth;
   Gtk::Label size;
   Gtk::HScale res_slider;
   Gtk::HScale size_slider;
   Gtk::HBox mouse_box, num_iter_box;
   Gtk::Label mouse_pos_x, mouse_pos_y, num_iter_label;
   Gtk::Table btn_table;
   Gtk::Button apply_btn, new_btn, save_btn, load_btn;
   Gtk::HSeparator hsep0, hsep1, hsep2;
};

#endif	// JULIASETWIDGET_H
