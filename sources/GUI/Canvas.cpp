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

#include <cmath>
#include <iostream>

#include <cairomm/context.h>

#include <gdkmm/general.h>

#include "Canvas.h"
#include "ViewerWidget.h"
#include "PointInputDlg.h"


Canvas::Canvas ( Glib::RefPtr < Gdk::Pixbuf > pixbuf, ViewerWidget &vw)
      : _pixbuf_image ( pixbuf )
{
//   add (_pixbuf_image);
	add_events(Gdk::POINTER_MOTION_MASK);
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::BUTTON_RELEASE_MASK);

	signal_motion_notify_event().connect(sigc::mem_fun(vw,
			&ViewerWidget::processMotionNotifyEvent));
	signal_button_press_event().connect(sigc::mem_fun(vw,
			&ViewerWidget::processButtonPressEvent));
	signal_button_release_event().connect(sigc::mem_fun(vw,
			&ViewerWidget::processButtonReleaseEvent));

	_image_sfc = Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, pixbuf->get_width(), pixbuf->get_height());

	// Create the new Context for the ImageSurface
	_image_context = Cairo::Context::create (_image_sfc);

	// Draw the image on the new Context
	Gdk::Cairo::set_source_pixbuf (_image_context, _pixbuf_image, 0.0, 0.0);
	_image_context->paint();
}

Canvas::~Canvas()
{}

void Canvas::on_realize()
{
	Gtk::DrawingArea::on_realize();
	Glib::RefPtr<Gdk::Window> win(get_window());
	std::cout << "[Canvas::on_realize()] size: " << get_width() << " x " << get_height() << std::endl;
	if (win) {
		Cairo::RefPtr<Cairo::Context> cairo_context (win->create_cairo_context());
		Gdk::Cairo::set_source_pixbuf(cairo_context, _pixbuf_image, 0, 0);
		on_draw(cairo_context);
	}
}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gdk::Cairo::set_source_pixbuf(cr, _pixbuf_image, 0, 0);
	cr->rectangle(0, 0, getWidth(), getHeight());
	cr->fill();
	cr->paint();

	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	// coordinates for the center of the window
	int xc, yc;
	xc = width / 2;
	yc = height / 2;

	cr->set_line_width(10.0);

	// draw red lines out from the center of the window
	cr->set_source_rgb(0.8, 0.0, 0.0);
	cr->move_to(0, 0);
	cr->line_to(xc, yc);
	cr->line_to(0, height);
	cr->move_to(xc, yc);
	cr->line_to(width, yc);
	cr->stroke();

	return true;
}

bool Canvas::on_expose_event(GdkEventExpose* event)
{
	std::cout << "[Canvas::on_expose_event]" << std::endl;
	Glib::RefPtr<Gdk::Window> window = get_window();
	const int width (get_width());
	const int height (get_height());
	std::cout << "[Canvas::on_expose_event] size: " << width << " x " << height << std::endl;
	if (window) {
		Cairo::RefPtr<Cairo::Context> cr(window->create_cairo_context());

	    // Store context
		cr->save();

	    // Draw the source image on the widget context
		cr->set_source (_image_sfc, 0.0, 0.0);
		cr->rectangle (0.0, 0.0, _pixbuf_image->get_width(), _pixbuf_image->get_height());
		cr->clip();
		cr->paint();

	    // Restore context
		cr->restore();

		const int width (getWidth());
		const int height (getHeight());

		// coordinates for the center of the window
		int xc, yc;
		xc = width / 2;
		yc = height / 2;

		cr->set_line_width(10.0);

		// draw red lines out from the center of the window
		cr->set_source_rgb(0.8, 0.0, 0.0);
		cr->move_to(0, 0);
		cr->line_to(xc, yc);
		cr->line_to(0, height);
		cr->move_to(xc, yc);
		cr->line_to(width, yc);
		cr->stroke();
	}
	return true;
}

unsigned Canvas::getWidth () const
{
   return _pixbuf_image->get_width();
}

unsigned Canvas::getHeight () const
{
   return _pixbuf_image->get_height();
}

Glib::RefPtr<Gdk::Pixbuf> const Canvas::getImagePixbuf() const
{
	return _pixbuf_image;
}

void Canvas::setImage ( Glib::RefPtr<Gdk::Pixbuf> pixbuf )
{
   _pixbuf_image = pixbuf;
}

