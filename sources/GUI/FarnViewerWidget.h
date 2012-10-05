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
 * Created on 05.10.2012 by fischeth
 * @file FarnViewerWidget.h
 */

#ifndef FARNVIEWERWIDGET_H_
#define FARNVIEWERWIDGET_H_

#include "ViewerWidget.h"

namespace GUI {

class FarnViewerWidget : public ViewerWidget
{
public:
	FarnViewerWidget(Fractal *fractal, MainWindow &parent);
	virtual ~FarnViewerWidget();

protected:
	virtual guint8* getData (Fractal const& input_fractal) const;
	virtual void onMovie ();
	virtual void onNewViewerWidget();
	virtual void onNewFractal ();
	virtual bool processMotionNotifyEvent(GdkEventMotion *event);
	virtual bool processButtonPressEvent ( GdkEventButton *event );
	virtual bool processButtonReleaseEvent ( GdkEventButton *event );

};

} // end namespace GUI

#endif /* FARNVIEWERWIDGET_H_ */
