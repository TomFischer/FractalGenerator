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
 * @file ViewerWidget.cpp
 *
 *  Created on: 02/2005
 *      Author: Thomas Fischer
 */

#include "ViewerWidget.h"
#include "MainWindow.h"
#include "utils.h"
#include <stdlib.h>

ViewerWidget::ViewerWidget ( Fractal *fractal, MainWindow &parent )
      : Gtk::VBox(), _parent (parent), _hbox (), _fractal ( fractal ),
        _canvas ( NULL ),
        _save_img_dlg (new Gtk::FileChooserDialog ( "Save fractal", Gtk::FILE_CHOOSER_ACTION_SAVE ))
{
//   if (tof == 0) mbs_wdgt = new ApfelmaennchenWidget ( *this );
//   else js_wdgt = new JuliaSetWidget (*this);
//
//   // make pixbuf from fractal
//   Glib::RefPtr <Gdk::Pixbuf> pixbuf (Gdk::Pixbuf::create_from_data
//		(getData (*fractal), Gdk::COLORSPACE_RGB, false, 8, fractal->getCols(),
//		fractal->getRows (), fractal->getCols() * 3));
//
//   // create with this pixbuf a Canvas
//   canvas = new Canvas ( pixbuf, *this );
//
//   // add these Canvas to this widget
//   hbox.pack_start ( *canvas, Gtk::PACK_SHRINK );
//
//   // make and add controls for fractal
//   if (tof == 0) hbox.pack_start(*mbs_wdgt, Gtk::PACK_EXPAND_PADDING );
//   else hbox.pack_start(*js_wdgt, Gtk::PACK_EXPAND_PADDING );
//
//   pack_start (hbox, Gtk::PACK_SHRINK);

   _save_img_dlg->add_button("Cancel", Gtk::RESPONSE_CANCEL);
   _save_img_dlg->add_button("Ok", Gtk::RESPONSE_OK);
}

ViewerWidget::~ViewerWidget()
{
   delete _fractal;
   delete _canvas;

   //if (js_wdgt) delete js_wdgt;
   delete _save_img_dlg;
}

void ViewerWidget::onSaveImg()
{
	int res = _save_img_dlg->run();

	switch (res) {
	case (Gtk::RESPONSE_OK): {
		_save_img_dlg->hide();
		std::string fname(_save_img_dlg->get_filename());

//		int screen_width(get_screen()->get_width());
//		int screen_height(get_screen()->get_height());
//		std::cout << "screen size: " << screen_width << " x " << screen_height
//				<< std::endl;
//
//		Fractal *tmp_fractal(new Apfelmaennchen(mbs_wdgt->getPoint(0),
//				mbs_wdgt->getPoint(1), screen_width, screen_height,
//				mbs_wdgt->getIterationDepth()));
//		// make pixbuf from fractal
//		Glib::RefPtr<Gdk::Pixbuf> tmp_pixbuf(Gdk::Pixbuf::create_from_data(
//				getData(*tmp_fractal), Gdk::COLORSPACE_RGB, false, 8,
//				tmp_fractal->getCols(), tmp_fractal->getRows(),
//				tmp_fractal->getCols() * 3));
//		tmp_pixbuf->save(fname, "png");
//		delete tmp_fractal;

		Gtk::Image const& img (_canvas->getImage());
		Glib::RefPtr<Gdk::Pixbuf>::cast_const (img.get_pixbuf())->save(fname, "png");
		break;
	}
	case (Gtk::RESPONSE_CANCEL): {
		_save_img_dlg->hide();
		break;
	}
	default: {
		std::cout << "Unexpected button clicked." << std::endl;
		break;
	}
	}
}

Fractal* ViewerWidget::getFractal ()
{
   return _fractal;
}

Canvas const* ViewerWidget::getCanvas () const
{
   return _canvas;
}
