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
* @file Canvas.cpp
*
*  Created on: 01/2005 by Thomas Fischer
*/

#include <cmath>
#include <iostream>

#include <cairomm/context.h>

#include <gdkmm/general.h>

#include "Canvas.h"
#include "ViewerWidget.h"
#include "PointInputDlg.h"


Canvas::Canvas ( Glib::RefPtr < Gdk::Pixbuf > pixbuf, ViewerWidget &vw)
      : _image_sfc (Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, pixbuf->get_width(), pixbuf->get_height()))
{
	add_events(Gdk::POINTER_MOTION_MASK);
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::BUTTON_RELEASE_MASK);

	signal_motion_notify_event().connect(sigc::mem_fun(vw,
			&ViewerWidget::processMotionNotifyEvent));
	signal_button_press_event().connect(sigc::mem_fun(vw,
			&ViewerWidget::processButtonPressEvent));
	signal_button_release_event().connect(sigc::mem_fun(vw,
			&ViewerWidget::processButtonReleaseEvent));

	// Create the new Context for the ImageSurface
	_image_context = Cairo::Context::create (_image_sfc);

	// Draw the image on the new Context
	Gdk::Cairo::set_source_pixbuf (_image_context, pixbuf, 0.0, 0.0);
	_image_context->paint();
}

Canvas::~Canvas()
{}

void Canvas::on_realize()
{
	Gtk::DrawingArea::on_realize();
	Glib::RefPtr<Gdk::Window> win(get_window());
}

bool Canvas::on_expose_event(GdkEventExpose* event)
{
	std::cout << "[Canvas::on_expose_event]" << std::endl;
	Glib::RefPtr<Gdk::Window> window = get_window();
	const int width (get_width());
	const int height (get_height());
	if (window) {
		Cairo::RefPtr<Cairo::Context> cr(window->create_cairo_context());

	    // Store context
		cr->save();

	    // Draw the source image on the widget context
		cr->set_source (_image_sfc, 0.0, 0.0);
		cr->rectangle (0.0, 0.0, get_width(), get_height());
		cr->clip();
		cr->paint();

	    // Restore context
		cr->restore();
	}
	return true;
}

unsigned Canvas::getWidth () const
{
   return get_width();
}

unsigned Canvas::getHeight () const
{
   return get_height();
}

void Canvas::setImage ( Glib::RefPtr<Gdk::Pixbuf> pixbuf )
{
	// create image surface
	_image_sfc = Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, pixbuf->get_width(), pixbuf->get_height());

	// Create the new Context for the ImageSurface
	_image_context = Cairo::Context::create (_image_sfc);

	// draw the image on the context
	Gdk::Cairo::set_source_pixbuf (_image_context, pixbuf, 0.0, 0.0);
	_image_context->paint();

	queue_draw();
}

