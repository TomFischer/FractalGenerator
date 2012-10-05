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
 * @file SierpinskyCarpetDrawingArea.h
 */

#ifndef SIERPINSKYCARPETDRAWINGAREA_H_
#define SIERPINSKYCARPETDRAWINGAREA_H_

#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>

namespace GUI {

class SierpinskyCarpetDrawingArea : public Gtk::DrawingArea
{
public:
	SierpinskyCarpetDrawingArea();
	virtual ~SierpinskyCarpetDrawingArea();
	virtual bool on_expose_event(GdkEventExpose* event);
};

}

#endif /* SIERPINSKYCARPETDRAWINGAREA_H_ */
