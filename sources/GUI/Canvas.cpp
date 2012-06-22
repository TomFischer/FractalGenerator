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

#include "Canvas.h"
#include "ViewerWidget.h"
#include "PointInputDlg.h"
#include <cmath>
#include <iostream>

Canvas::Canvas ( Glib::RefPtr < Gdk::Pixbuf > apixbuf, ViewerWidget &vw)
      : Gtk::EventBox(),
      viewer_widget (vw), _image ( apixbuf ),
      width ( apixbuf->get_width () ), height ( apixbuf->get_height () )
{
   add (_image);
   add_events ( Gdk::POINTER_MOTION_MASK );
   add_events ( Gdk::BUTTON_PRESS_MASK );
   add_events ( Gdk::BUTTON_RELEASE_MASK );

   signal_motion_notify_event().connect (
      sigc::mem_fun (viewer_widget, &ViewerWidget::processMotionNotifyEvent));
   signal_button_press_event().connect(
      sigc::mem_fun(viewer_widget, &ViewerWidget::processButtonPressEvent) );
   signal_button_release_event().connect(
      sigc::mem_fun(viewer_widget, &ViewerWidget::processButtonReleaseEvent) );

   set_resize_mode ( Gtk::RESIZE_PARENT );
}

Canvas::~Canvas()
{}

unsigned Canvas::getWidth () const
{
   return _image.get_pixbuf()->get_width();
}

unsigned Canvas::getHeight () const
{
   return _image.get_pixbuf()->get_height();
}

void Canvas::setImage ( Glib::RefPtr<Gdk::Pixbuf> pixbuf )
{
   _image.set (pixbuf);
}

Gtk::Image const& Canvas::getImage() const
{
	return _image;
}
