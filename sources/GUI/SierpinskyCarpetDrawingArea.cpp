/**
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
 * Created on 05.10.2012 by Thomas Fischer
 * @file SierpinskyCarpetDrawingArea.cpp
 */

#include <SierpinskyCarpetDrawingArea.h>

namespace GUI {

SierpinskyCarpetDrawingArea::SierpinskyCarpetDrawingArea()
{
	set_size_request (500,500);

	queue_draw();
}

SierpinskyCarpetDrawingArea::~SierpinskyCarpetDrawingArea()
{}

bool SierpinskyCarpetDrawingArea::on_expose_event(GdkEventExpose* event)
{
	Glib::RefPtr<Gdk::Window> window = get_window();
	const int width (get_width());
	const int height (get_height());
	if (window) {
		Cairo::RefPtr<Cairo::Context> cr(window->create_cairo_context());

		// Store context
		cr->save();

		cr->rectangle(0, 0, width, height);
		cr->fill();
		cr->paint();

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

		// Restore context
		cr->restore();
	}

	return true;
}

} // end namespace GUI
