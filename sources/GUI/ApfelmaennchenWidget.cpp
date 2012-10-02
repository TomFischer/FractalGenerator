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
* @file ApfelmaennchenWidget.cpp
*
*  Created on 02/2005 by Thomas Fischer
*/

#include "ApfelmaennchenWidget.h"
#include "Apfelmaennchen.h"
#include "ViewerWidget.h"
#include "Canvas.h"
#include "lexical_cast.h"

#include <iostream>
#include <gtkmm/colorselection.h>

ApfelmaennchenWidget::ApfelmaennchenWidget ( ViewerWidget &vw )
      : Gtk::VBox (), viewer_widget (vw),
      geometry_box (),
      left_lower_input_dlg (),
      right_upper_input_dlg (),
      iteration_depth ("number of iterations"),
      size ("resolution"),
      res_slider (50, 1000, 10),
      size_slider (50, 1000, 1),
      mouse_box (), num_iter_box (),
      mouse_pos_x ("0.0"), mouse_pos_y ("0.0"), num_iter_label ("0"),
      overview_img (),
      btn_table ( 2, 2 ),
      apply_btn ("Apply"), new_btn ("New"),
      save_btn ("Save Image"),
      movie_btn ("Movie"), hsep0 ()
{
   // set_shadow_type ( Gtk::SHADOW_IN );
   left_lower_input_dlg.setCoordinate(0, vw.getFractal()->getUpperLeftPoint()[0]);
   left_lower_input_dlg.setCoordinate(1, vw.getFractal()->getUpperLeftPoint()[1]);
   left_lower_input_dlg.setNameOfPoint ("left upper");
   right_upper_input_dlg.setCoordinate(0, vw.getFractal()->getLowerRightPoint()[0]);
   right_upper_input_dlg.setCoordinate(1, vw.getFractal()->getLowerRightPoint()[1]);
   right_upper_input_dlg.setNameOfPoint ("right lower");

   geometry_box.pack_start ( left_lower_input_dlg, Gtk::PACK_SHRINK );
   geometry_box.pack_start ( right_upper_input_dlg, Gtk::PACK_SHRINK );
   // pack iteration-label into box
   geometry_box.pack_start ( iteration_depth, Gtk::PACK_SHRINK, 10 );
   res_slider.set_value ( vw.getFractal()->getMaxIterations ());
   geometry_box.pack_start ( res_slider );
   // pack resolution-label into box
   geometry_box.pack_start ( size );
   size_slider.set_value (vw.getFractal()->getRows ());
   geometry_box.pack_start ( size_slider );

   pack_start ( geometry_box );
   pack_start (hsep0);

   num_iter_box.add (num_iter_label);
   pack_start (hsep0);

   mouse_box.add (mouse_pos_x);
   mouse_box.add (mouse_pos_y);
   pack_start ( mouse_box, Gtk::PACK_SHRINK );
   pack_start ( num_iter_box, Gtk::PACK_SHRINK );
   new_btn.signal_clicked().connect ( sigc::mem_fun (viewer_widget,
                                      &ViewerWidget::onNewViewerWidget ) );
   apply_btn.signal_clicked().connect ( sigc::mem_fun (viewer_widget,
                                        &ViewerWidget::onNewFractal ) );
   save_btn.signal_clicked().connect ( sigc::mem_fun (viewer_widget,
                                       &ViewerWidget::onSaveImg ) );
   movie_btn.signal_clicked().connect ( sigc::mem_fun (viewer_widget,
                                        &ViewerWidget::onMovie ) );

   update ();
   pack_start (hsep0);
   pack_start (overview_img);
   btn_table.attach (new_btn, 0, 1, 0, 1);
   btn_table.attach (apply_btn, 1, 2, 0, 1);
   btn_table.attach (save_btn, 0, 1, 1, 2);
   btn_table.attach (movie_btn, 1, 2, 1, 2);
   pack_start (btn_table, Gtk::PACK_SHRINK);
}

ApfelmaennchenWidget::~ApfelmaennchenWidget()
{}

Point2D ApfelmaennchenWidget::getPoint ( size_t num ) const
{
   if (num == 0) {
      double p[2];
      p[0]= left_lower_input_dlg.getCoordinate (0);
      p[1] = left_lower_input_dlg.getCoordinate (1);
      return Point2D (p);
   } else {
      double p[2];
      p[0] = right_upper_input_dlg.getCoordinate (0);
      p[1] = right_upper_input_dlg.getCoordinate (1);
      return Point2D (p);
   }
}

size_t ApfelmaennchenWidget::getIterationDepth () const
{
   return (size_t)res_slider.get_value();
}

size_t ApfelmaennchenWidget::getSize () const
{
   return (size_t)size_slider.get_value();
}

void ApfelmaennchenWidget::actualizePointerPosition ( int x, int y )
{
   Fractal const*const frac (viewer_widget.getFractal());
   Point2D const& p0(frac->getUpperLeftPoint());
   Point2D const& p1(frac->getLowerRightPoint());

   const unsigned x_pix_size (frac->getRows ());
   const unsigned y_pix_size (frac->getCols ());

   const double xcoord (((p1[0] - p0[0]) * y) / x_pix_size + p0[0]);
   const double ycoord (((p1[1] - p0[1]) * x) / y_pix_size + p0[1]);

   unsigned num_iter = 0;
   if (0 <= x and x < x_pix_size and 0 <= y and y < y_pix_size) {
      num_iter = (*frac)(y,x);
   }

   const std::string label_x((lexical_cast <std::string> (xcoord)).substr(0, 8));
   const std::string label_y((lexical_cast <std::string> (ycoord)).substr(0, 8));
   const std::string label_num_iter(lexical_cast <std::string> (num_iter));

   mouse_pos_x.set_text ( label_x.c_str () );
   mouse_pos_y.set_text ( label_y.c_str () );
   num_iter_label.set_text ( label_num_iter.c_str ());
}

PointInputDlg& ApfelmaennchenWidget::getPointInputDlg ( unsigned point )
{
   if (point == 0) return left_lower_input_dlg;
   else return right_upper_input_dlg;
}

void ApfelmaennchenWidget::onCoordinateChanged(unsigned dim, unsigned x, unsigned y)
{
	Point2D const &p0(viewer_widget.getFractal()->getUpperLeftPoint());
	Point2D const &p1(viewer_widget.getFractal()->getLowerRightPoint());

	const unsigned width ((viewer_widget.getCanvas())->getWidth());
	const unsigned height ((viewer_widget.getCanvas())->getHeight());
	const double dy = ((p1[0] - p0[0]) * y) / width + p0[0];
	const double dx = ((p1[1] - p0[1]) * x) / height + p0[1];

	getPointInputDlg(dim).setCoordinate(0, dy);
	getPointInputDlg(dim).setCoordinate(1, dx);
}

guint8* ApfelmaennchenWidget::getData()
{
   double *op0 (new double[2]), *op1(new double[2]); // overview points
   op0[0] = -2.0;
   op0[1] = -2.0;
   op1[0] = 2.0;
   op1[1] = 2.0;
   Point2D p0 (op0), p1 (op1);
   size_t rows(150), cols(150);
   Apfelmaennchen *mbs (new Apfelmaennchen (p0, p1, rows, cols, 300));

   size_t nob(3); //number of bytes

   guint8* data = new guint8[nob*rows*cols];

   for (size_t r=0; r<rows; ++r) {
      for (size_t c=0; c<cols; ++c) {
         if ( (*mbs)(r,c) < 10 ) {
            // outer space
            data[nob * (r * cols + c)] = (4 * (*mbs)(r,c));
            data[nob * (r * cols + c) + 1] = (4 * (*mbs)(r,c));
            data[nob * (r * cols + c) + 2] = (25 * (*mbs)(r,c));
         }
         if ( 10 <= (*mbs)(r,c) and (*mbs)(r,c) < 64) {
            // border of body
            data[nob * (r * cols + c)] = 255 - 4 * ((*mbs)(r,c)-10)-1;
            data[nob * (r * cols + c) + 1] = 255 - 4 * ((*mbs)(r,c)-10)-1;
            data[nob * (r * cols + c) + 2] = 255 - 1 * ((*mbs)(r,c)-10);
         }
         if ( 64 <= (*mbs)(r,c) and  (*mbs)(r,c) < 128 ) {
            data[nob * (r * cols + c)] = 4 * ((*mbs)(r,c) - 64);
            data[nob * (r * cols + c) + 1] = 2 * ((*mbs)(r,c) - 64);
            data[nob * (r * cols + c) + 2] = ((*mbs)(r,c) - 64);
         }
         if ( (*mbs)(r,c) >  128) {
            // body
            data[nob * (r * cols + c)] = ((*mbs)(r,c)-128) % 32;
            data[nob * (r * cols + c) + 1] = ((*mbs)(r,c)-128) % 255;
            data[nob * (r * cols + c) + 2] = ((*mbs)(r,c)-128) % 255;
         }
      }
   }

   // coordinate transformation
   double ax (mbs->getUpperLeftPoint()[0]);
   double bx (mbs->getLowerRightPoint()[0]);
   double ay (mbs->getUpperLeftPoint()[1]);
   double by (mbs->getLowerRightPoint()[1]);

   double *dp0 (new double[2]), *dp1(new double[2]); // detail view points
   dp0[0] = viewer_widget.getFractal()->getUpperLeftPoint()[0];
   dp0[1] = viewer_widget.getFractal()->getUpperLeftPoint()[1];
   dp1[0] = viewer_widget.getFractal()->getLowerRightPoint()[0];
   dp1[1] = viewer_widget.getFractal()->getLowerRightPoint()[1];

   double x0 ((dp0[0]-ax)/(bx-ax));
   double x1 ((dp1[0]-ax)/(bx-ax));
   double y0 ((dp0[1]-ay)/(by-ay));
   double y1 ((dp1[1]-ay)/(by-ay));

   unsigned xpix0 (static_cast<unsigned>(x0 * mbs->getRows()));
   unsigned xpix1 (static_cast<unsigned>(x1*mbs->getRows()-1));
   unsigned ypix0 (static_cast<unsigned>(y0 * mbs->getCols()));
   unsigned ypix1 (static_cast<unsigned>(y1 * mbs->getCols()-1));

   std::cout << "(xpix0, ypix0): (" << xpix0 << "," << ypix0 << ")" <<std::endl;
   std::cout << "(xpix1, ypix1): (" << xpix1 << "," << ypix1 << ")" <<std::endl;

   // draw
   for (size_t c=ypix0; c<ypix1; ++c) {
      data[nob*(xpix0*cols+c)] = data[nob*(xpix0*cols+c)]^255;
      data[nob*(xpix0*cols+c)+1] = data[nob*(xpix0*cols+c)+1]^255;
      data[nob*(xpix0*cols+c)+2] = data[nob*(xpix0*cols+c)+2]^255;
   }
   for (size_t c=ypix0; c<ypix1; ++c) {
      data[nob*(xpix1*cols+c)] = data[nob*(xpix1*cols+c)]^255;
      data[nob*(xpix1*cols+c)+1] = data[nob*(xpix1*cols+c)+1]^255;
      data[nob*(xpix1*cols+c)+2] = data[nob*(xpix1*cols+c)+2]^255;
   }
   for (size_t r=xpix0; r<xpix1; ++r) {
      data[nob*(r*cols+ypix0)] = data[nob*(r*cols+ypix0)]^255;
      data[nob*(r*cols+ypix0)+1] = data[nob*(r*cols+ypix0)+1]^255;
      data[nob*(r*cols+ypix0)+2] = data[nob*(r*cols+ypix0)+2]^255;
   }
   for (size_t r=xpix0; r<xpix1; ++r) {
      data[nob*(r*cols+ypix1)] = data[nob*(r*cols+ypix1)]^255;
      data[nob*(r*cols+ypix1)+1] = data[nob*(r*cols+ypix1)+1]^255;
      data[nob*(r*cols+ypix1)+2] = data[nob*(r*cols+ypix1)+2]^255;
   }

   delete [] op0;
   delete [] op1;
   delete [] dp0;
   delete [] dp1;
   delete mbs;
   return data;
}

void ApfelmaennchenWidget::update ()
{
   guint8 *raw_data (getData());
   Glib::RefPtr<Gdk::Pixbuf> pixbuf (Gdk::Pixbuf::create_from_data(raw_data,
                                     Gdk::COLORSPACE_RGB, false, 8, 150, 150, 150*3));
   overview_img.set (pixbuf);
}


