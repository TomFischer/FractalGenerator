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
*/

/*
 * @file ViewerWidget.h
 *
 *  Created on: 02/2005
 *      Author: Thomas Fischer
 */

#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <gtkmm/box.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menu.h>
#include <gtkmm/main.h>
#include <gtkmm/filechooserdialog.h>

#include <string>

#include "Fractal.h"
#include "Canvas.h"
#include "ApfelmaennchenWidget.h"
#include "JuliaSetWidget.h"

class MainWindow;

class ViewerWidget : public Gtk::VBox
{
public:
   ViewerWidget (Fractal *fractal, MainWindow &parent);
   virtual ~ViewerWidget();
   void onSaveImg ();
   virtual void onMovie () {};
   virtual void onNewViewerWidget() {};
   virtual void onNewFractal () {};

   Fractal* getFractal ();
   Canvas const* getCanvas () const;

   /**
   	 * method for event handling motion notify event
   	 * @param event
   	 * @return
   	 */
   	virtual bool processMotionNotifyEvent(GdkEventMotion *event) { return true; }
   	virtual bool processButtonPressEvent(GdkEventButton *event) { return true; };
   	virtual bool processButtonReleaseEvent(GdkEventButton *event) { return true; };

protected:
   virtual guint8* getData(Fractal const& input_fractal) const {};

   MainWindow &_parent;
   /**
    * horizontal box for depicting the fractal within a canvas object and the fractal settings widget
    */
   Gtk::HBox _hbox;
   Fractal *_fractal;
   Canvas *_canvas;
   Gtk::FileChooserDialog *_save_img_dlg;
};

#endif	//VIEWERWIDGET_H
