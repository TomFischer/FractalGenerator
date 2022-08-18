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
 * @file SierpinskyCarpetViewerWidget.h
 */

#ifndef SIERPINSKYCARPETVIEWERWIDGET_H_
#define SIERPINSKYCARPETVIEWERWIDGET_H_

#include "ViewerWidget.h"
#include "SierpinskyCarpetDrawingArea.h"

namespace GUI {

class SierpinskyCarpetViewerWidget: public ViewerWidget
{
public:
	SierpinskyCarpetViewerWidget(Fractal *fractal, MainWindow &parent);
	virtual ~SierpinskyCarpetViewerWidget();

    guint8* getData([[maybe_unused]] Fractal const& input_fractal) const
    {
        return nullptr;
    }

private:
	GUI::SierpinskyCarpetDrawingArea _drawing_area;

};

} // end namespace GUI

#endif /* SIERPINSKYCARPETVIEWERWIDGET_H_ */
