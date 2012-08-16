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
      : _image ( pixbuf )
{
//   add (_image);
	add_events(Gdk::POINTER_MOTION_MASK);
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::BUTTON_RELEASE_MASK);

	signal_motion_notify_event().connect(sigc::mem_fun(vw,
			&ViewerWidget::processMotionNotifyEvent));
	signal_button_press_event().connect(sigc::mem_fun(vw,
			&ViewerWidget::processButtonPressEvent));
	signal_button_release_event().connect(sigc::mem_fun(vw,
			&ViewerWidget::processButtonReleaseEvent));
//   set_resize_mode ( Gtk::RESIZE_PARENT );

	_image_sfc = Cairo::ImageSurface::create(Cairo::FORMAT_RGB24, pixbuf->get_width(), pixbuf->get_height());
//	image_context_ptr_ = Cairo::Context::create(_image_sfc);
//	        Gdk::Cairo::set_source_pixbuf(image_context_ptr_, image_ptr_, 0.0,
//	0.0);
//	image_context_ptr_->paint();

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
		Gdk::Cairo::set_source_pixbuf(cairo_context, _image.get_pixbuf(), 0, 0);
		on_draw(cairo_context);
	}
}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
//	Gdk::Cairo::set_source_pixbuf(cr, _image.get_pixbuf(), 0, 0);
//	cr->rectangle(0, 0, getWidth(), getHeight());
//	cr->fill();
//	cr->paint();
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

		cr->rectangle(0, 0, getWidth(), getHeight());
		//event->area.x, event->area.y,	event->area.width, event->area.height);
		cr->clip();

		cr->set_source(_image_sfc, 0, 0);

		cr->rectangle(0.0, 0.0, getWidth(), getHeight());
		cr->clip();
		cr->paint();
//		Gdk::Cairo::set_source_pixbuf(cr, _image.get_pixbuf(), 0, 0);

//		const int width (getWidth());
//		const int height (getHeight());
//
//		// coordinates for the center of the window
//		int xc, yc;
//		xc = width / 2;
//		yc = height / 2;
//
//		cr->set_line_width(10.0);
//
//		// draw red lines out from the center of the window
//		cr->set_source_rgb(0.8, 0.0, 0.0);
//		cr->move_to(0, 0);
//		cr->line_to(xc, yc);
//		cr->line_to(0, height);
//		cr->move_to(xc, yc);
//		cr->line_to(width, yc);
		cr->stroke();
	}
	return true;
}

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
