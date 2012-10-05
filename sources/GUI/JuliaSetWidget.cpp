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
 * @file JuliaSetWidget.cpp
 *
 *  Created on: 02/2008
 *      Author: Thomas Fischer
 */

#include "JuliaSetWidget.h"
#include "JuliaSet.h"
#include "ViewerWidget.h"
#include "Canvas.h"
#include "lexical_cast.h"

JuliaSetWidget::JuliaSetWidget ( ViewerWidget &vw )
      : Gtk::VBox (), viewer_widget (vw), _geometric_properties_frame("geometric properties"),
      _geometry_box (),
      iteration_depth ("number of iterations"),
      size ("resolution"),
      res_slider (50, 1000, 10),
      size_slider (50, 1000, 1),
      mouse_box (), num_iter_box (),
      mouse_pos_x ("0.0"), mouse_pos_y ("0.0"), num_iter_label ("0"),
      btn_table ( 2, 2 ),
      apply_btn ("Apply"), new_btn ("New"),
      save_btn ("Save Parameters"),
      load_btn ("Load Parameters"), hsep0 ()
{
	_geometric_properties_frame.add(_geometry_box);

	_upper_left_point_input_dlg.setCoordinate (0, vw.getFractal()->getUpperLeftPoint()[0]);
	_upper_left_point_input_dlg.setCoordinate(1, vw.getFractal()->getUpperLeftPoint()[1]);
	_upper_left_point_input_dlg.setNameOfPoint ("upper left point");

	_lower_right_point_input_dlg.setCoordinate (0, vw.getFractal()->getLowerRightPoint()[0]);
	_lower_right_point_input_dlg.setCoordinate(1, vw.getFractal()->getLowerRightPoint()[1]);
	_lower_right_point_input_dlg.setNameOfPoint ("lower right point");

	_lower_right_point_input_dlg.setCoordinate (0, vw.getFractal()->getLowerRightPoint()[0]);
	_lower_right_point_input_dlg.setCoordinate(1, vw.getFractal()->getLowerRightPoint()[1]);
	_lower_right_point_input_dlg.setNameOfPoint ("lower right point");

	JuliaSet const*const julia_set(dynamic_cast<JuliaSet*>(vw.getFractal()));
	_complex_parameter_input_dlg.setCoordinate (0, julia_set->getComplexParameter()[0]);
	_complex_parameter_input_dlg.setCoordinate(1, julia_set->getComplexParameter()[1]);
	_complex_parameter_input_dlg.setNameOfPoint ("complex parameter");

   _geometry_box.pack_start ( _complex_parameter_input_dlg, Gtk::PACK_SHRINK );
   _geometry_box.pack_start ( _upper_left_point_input_dlg, Gtk::PACK_SHRINK );
   _geometry_box.pack_start ( _lower_right_point_input_dlg, Gtk::PACK_SHRINK );

   // pack iteration-label into box
   _geometry_box.pack_start ( iteration_depth, Gtk::PACK_SHRINK, 10 );

   res_slider.set_value ( vw.getFractal()->getMaxIterations ());
   _geometry_box.pack_start ( res_slider );
   // pack resolution-label into box
   _geometry_box.pack_start ( size );
   size_slider.set_value (vw.getFractal()->getRows ());
   _geometry_box.pack_start ( size_slider );

   pack_start(_geometric_properties_frame, Gtk::PACK_SHRINK );
   pack_start(hsep0);
   num_iter_box.add (num_iter_label);
   pack_start (hsep1);
   mouse_box.add (mouse_pos_x);
   mouse_box.add (mouse_pos_y);
   pack_start ( mouse_box, Gtk::PACK_SHRINK );
   pack_start ( num_iter_box, Gtk::PACK_SHRINK );
   new_btn.signal_clicked().connect ( sigc::mem_fun (viewer_widget,
                                      &ViewerWidget::onNewViewerWidget ) );
   apply_btn.signal_clicked().connect ( sigc::mem_fun (viewer_widget,
                                        &ViewerWidget::onNewFractal ) );

   pack_start (hsep2);
   btn_table.attach (new_btn, 0, 1, 0, 1);
   btn_table.attach (apply_btn, 1, 2, 0, 1);
   btn_table.attach (save_btn, 0, 1, 1, 2);
   btn_table.attach (load_btn, 1, 2, 1, 2);
   pack_start (btn_table, Gtk::PACK_SHRINK);
}

JuliaSetWidget::~JuliaSetWidget()
{}

Point2D JuliaSetWidget::getComplexParameter() const
{
   double p[2];
   p[0] = _complex_parameter_input_dlg.getCoordinate(0);
   p[1] = _complex_parameter_input_dlg.getCoordinate(1);
   return Point2D(p);
}

size_t JuliaSetWidget::getIterationDepth () const
{
   return (size_t)res_slider.get_value();
}

size_t JuliaSetWidget::getSize () const
{
   return (size_t)size_slider.get_value();
}

void JuliaSetWidget::actualizePointerPosition ( int x, int y )
{
   double p0[2], p1[2];
   Fractal* frac = viewer_widget.getFractal();
   p0[0] = frac->getUpperLeftPoint()[0];
   p0[1] = frac->getUpperLeftPoint()[1];
   p1[0] = frac->getLowerRightPoint()[0];
   p1[1] = frac->getLowerRightPoint()[1];

   unsigned x_pix_size = frac->getRows ();
   unsigned y_pix_size = frac->getCols ();

   double xcoord = ((p1[0] - p0[0]) * y) / x_pix_size + p0[0];
   double ycoord = ((p1[1] - p0[1]) * x) / y_pix_size + p0[1];

   unsigned num_iter = 0;
   if (0 <= x and x < x_pix_size and 0 <= y and y < y_pix_size) {
      num_iter = (*frac)(y,x);
   }

   std::string label_x = lexical_cast <std::string> (xcoord);
   std::string label_y = lexical_cast <std::string> (ycoord);
   std::string label_num_iter = lexical_cast <std::string> (num_iter);

   mouse_pos_x.set_text ( label_x.c_str () );
   mouse_pos_y.set_text ( label_y.c_str () );
   num_iter_label.set_text ( label_num_iter.c_str ());
}

void JuliaSetWidget::onCoordinateChanged (unsigned dim, unsigned x, unsigned y )
{
   Point2D const& p0(viewer_widget.getFractal()->getUpperLeftPoint ());
   Point2D const& p1(viewer_widget.getFractal()->getLowerRightPoint ());

   unsigned width  = (viewer_widget.getCanvas())->getWidth ();
   unsigned height = (viewer_widget.getCanvas())->getHeight();

   double dy = ((p1[0] - p0[0]) * y) / width;
   dy += p0[0];

   double dx = ((p1[1] - p0[1]) * x) / height;
   dx += p0[1];

   std::cout << "Button pressed at (" << dy << "," << dx << ")";
   std::cout << std::endl;
}

























