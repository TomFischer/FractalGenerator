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
 * @file Canvas.cpp
 *
 *  Created on: 01/2005
 *      Author: Thomas Fischer
 */

#include "lexical_cast.h"
#include "Canvas.h"
#include "ViewerWidget.h"
#include "PointInputDlg.h"
#include <cmath>
#include <iostream>

Canvas::Canvas ( Glib::RefPtr < Gdk::Pixbuf > apixbuf, ViewerWidget &vw)
      : Gtk::EventBox(),
      viewer_widget (vw), image ( apixbuf ),
      width ( apixbuf->get_width () ), height ( apixbuf->get_height () )
{
   add (image);
   add_events ( Gdk::POINTER_MOTION_MASK );
   add_events ( Gdk::BUTTON_PRESS_MASK );
   add_events ( Gdk::BUTTON_RELEASE_MASK );

   signal_motion_notify_event().connect (
      sigc::mem_fun (*this, &Canvas::onMotionNotifyEvent));
   signal_button_press_event().connect(
      sigc::mem_fun(*this, &Canvas::onButtonPressEvent) );
   signal_button_release_event().connect(
      sigc::mem_fun(*this, &Canvas::onButtonReleaseEvent) );

   set_resize_mode ( Gtk::RESIZE_PARENT );
}

Canvas::~Canvas()
{}

bool Canvas::onMotionNotifyEvent ( GdkEventMotion *event )
{
   unsigned x = lexical_cast <unsigned> (event->x);
   unsigned y = lexical_cast <unsigned> (event->y);
   if (viewer_widget.getApfelmaennchenWidget())
      viewer_widget.getApfelmaennchenWidget ()->actualizePointerPosition (x, y);
   /*else
      viewer_widget.getJuliaSetWidget ()->actualizePointerPosition (x, y);*/

   return true;
}

bool Canvas::onButtonPressEvent ( GdkEventButton *event )
{
   x0 = lexical_cast <unsigned> (event->x);
   y0 = lexical_cast <unsigned> (event->y);
   if (viewer_widget.getApfelmaennchenWidget())
      viewer_widget.getApfelmaennchenWidget()->onCoordinateChanged (0, x0, y0);
   /*else
      viewer_widget.getJuliaSetWidget ()->actualizePointerPosition (x0, y0);*/

   return true;
}

bool Canvas::onButtonReleaseEvent ( GdkEventButton *event )
{
   unsigned x = lexical_cast <unsigned> (event->x);
   unsigned y = lexical_cast <unsigned> (event->y);
   unsigned mid = unsigned(0.5*(abs(x - x0)+abs(y - y0)));
   unsigned temp;
   if (x0 < x) x = x0 + mid;
   else {
      temp = x0 - mid;
      x = x0;
      x0 = temp;
   }
   if (y0 < y) y = y0 + mid;
   else {
      temp = y0 - mid;
      y = y0;
      y0 = temp;
   }
   if (dynamic_cast<Apfelmaennchen*>(viewer_widget.getFractal())) {
	   viewer_widget.getApfelmaennchenWidget()->onCoordinateChanged (0, x0, y0);
	   viewer_widget.getApfelmaennchenWidget()->onCoordinateChanged (1, x, y);
   } else {
       viewer_widget.getJuliaSetWidget()->onCoordinateChanged (1, x, y);
   }

   return true;
}

unsigned Canvas::getWidth ()
{
   return image.get_pixbuf()->get_width();
}

unsigned Canvas::getHeight ()
{
   return image.get_pixbuf()->get_height();
}

void Canvas::setImage ( Glib::RefPtr<Gdk::Pixbuf> pixbuf )
{
   image.set (pixbuf);
}
