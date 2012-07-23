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
 * Created on 23.07.2012 by Thomas Fischer
 * @file JuliaSetViewerWidget.h
 */

#ifndef JULIASETVIEWERWIDGET_H_
#define JULIASETVIEWERWIDGET_H_


#include "ViewerWidget.h"
#include "JuliaSetWidget.h"
#include "Fractal.h"
#include "MainWindow.h"

namespace GUI {

class JuliaSetViewerWidget: public ViewerWidget
{
public:
	JuliaSetViewerWidget(Fractal *fractal, MainWindow &parent);
	virtual ~JuliaSetViewerWidget();
protected:
	virtual guint8* getData (Fractal const& input_fractal) const;
	virtual void onMovie ();
	virtual void onNewViewerWidget();
	virtual void onNewFractal ();
	virtual bool processMotionNotifyEvent(GdkEventMotion *event);
	virtual bool processButtonPressEvent ( GdkEventButton *event );
	virtual bool processButtonReleaseEvent ( GdkEventButton *event );
private:
	JuliaSetWidget _julia_wdgt;

};

} // end namespace GUI

#endif /* JULIASETVIEWERWIDGET_H_ */
