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
 * @file Canvas.h
 *
 *  Created on: 01/2005
 *      Author: Thomas Fischer
 */

#ifndef CANVAS_H_
#define CANVAS_H_

#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/eventbox.h>

class ViewerWidget;

class Canvas : public Gtk::EventBox
{
public:
   Canvas ();
   Canvas ( Glib::RefPtr <Gdk::Pixbuf> pixbuf, ViewerWidget &vw );
   virtual ~Canvas();
   void setImage ( Glib::RefPtr <Gdk::Pixbuf> pixbuf );
   void save ( const std::string &filename, const std::string &type);
   bool onMotionNotifyEvent ( GdkEventMotion *event );
   bool onButtonPressEvent ( GdkEventButton *event );
   bool onButtonReleaseEvent ( GdkEventButton *event );
   unsigned getWidth ();
   unsigned getHeight ();

private:
   ViewerWidget &viewer_widget;
   Gtk::Image image;
   unsigned width, height;
   //saved to receive equal height and width
   unsigned x0, y0;
};

#endif	//CANVAS_H
