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
//	set_size_request (500,500);
//	queue_draw();
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

		unsigned side_len_of_square (static_cast<unsigned>(std::min(width, height)));

		cr->set_line_width(1.0);

		// white
		cr->set_source_rgb(1.0, 1.0, 1.0);

		Point2D upper_left, lower_right;
		upper_left[0] = xc-side_len_of_square/2;
		upper_left[1] = yc-side_len_of_square/2;
		lower_right[0] = xc+side_len_of_square/2;
		lower_right[1] = yc+side_len_of_square/2;

		recursiveDescent(upper_left, lower_right, 6, cr);

		cr->stroke();

		// Restore context
		cr->restore();
	}

	return true;
}

void SierpinskyCarpetDrawingArea::recursiveDescent(Point2D const& upper_left, Point2D const& lower_right, unsigned level, Cairo::RefPtr<Cairo::Context> cr)
{
	double dx (lower_right[0] - upper_left[0]);
	double dy (lower_right[1] - upper_left[1]);
	// compute points
	Point2D grid_pnts[16];
	for (unsigned i(0); i<4; i++) {
		for (unsigned j(0); j<4; j++) {
			(grid_pnts[i*4+j])[0] = upper_left[0] + i * dx/3.0;
			(grid_pnts[i*4+j])[1] = upper_left[1] + j * dy/3.0;
		}
	}

	if (level > 1) {
		recursiveDescent(grid_pnts[0], grid_pnts[5], level-1, cr);
		recursiveDescent(grid_pnts[1], grid_pnts[6], level-1, cr);
		recursiveDescent(grid_pnts[2], grid_pnts[7], level-1, cr);

		recursiveDescent(grid_pnts[4], grid_pnts[9], level-1, cr);
		recursiveDescent(grid_pnts[6], grid_pnts[11], level-1, cr);

		recursiveDescent(grid_pnts[8], grid_pnts[13], level-1, cr);
		recursiveDescent(grid_pnts[9], grid_pnts[14], level-1, cr);
		recursiveDescent(grid_pnts[10], grid_pnts[15], level-1, cr);
	} else {
		drawRectangle(grid_pnts[0], grid_pnts[5], cr);
		drawRectangle(grid_pnts[1], grid_pnts[6], cr);
		drawRectangle(grid_pnts[2], grid_pnts[7], cr);

		drawRectangle(grid_pnts[4], grid_pnts[9], cr);
		drawRectangle(grid_pnts[6], grid_pnts[11], cr);

		drawRectangle(grid_pnts[8], grid_pnts[13], cr);
		drawRectangle(grid_pnts[9], grid_pnts[14], cr);
		drawRectangle(grid_pnts[10], grid_pnts[15], cr);
	}
}

void SierpinskyCarpetDrawingArea::drawRectangle(Point2D const& upper_left, Point2D const& lower_right, Cairo::RefPtr<Cairo::Context> cr)
{
	cr->move_to(upper_left[0], upper_left[1]);
	cr->line_to(upper_left[0], lower_right[1]);
	cr->line_to(lower_right[0], lower_right[1]);
	cr->line_to(lower_right[0], upper_left[1]);
	cr->line_to(upper_left[0], upper_left[1]);
}

} // end namespace GUI
