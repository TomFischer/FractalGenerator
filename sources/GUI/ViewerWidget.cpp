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
}

ViewerWidget::~ViewerWidget()
{
   delete _fractal;
   delete _canvas;

   delete _save_img_dlg;
}

void ViewerWidget::onSaveImg()
{
	int res = _save_img_dlg->run();

    switch (res)
    {
        case (Gtk::RESPONSE_OK):
        {
            _save_img_dlg->hide();
            std::string fname(_save_img_dlg->get_filename());

            int screen_width(get_screen()->get_width());
            int screen_height(get_screen()->get_height());
            std::cout << "screen size: " << screen_width << " x "
                      << screen_height << std::endl;

            Fractal* tmp_fractal(new Apfelmaennchen(
                _fractal->getUpperLeftPoint(), _fractal->getLowerRightPoint(),
                3 * _fractal->getCols(), 3 * _fractal->getRows(),
                _fractal->getMaxIterations()));
            // make pixbuf from fractal
            std::cout << "fractal size: " << tmp_fractal->getCols() << " x "
                      << tmp_fractal->getRows() << std::endl;
            Glib::RefPtr<Gdk::Pixbuf> tmp_pixbuf(Gdk::Pixbuf::create_from_data(
                getData(*tmp_fractal), Gdk::COLORSPACE_RGB, false, 8,
                tmp_fractal->getCols(), tmp_fractal->getRows(),
                tmp_fractal->getCols() * 3));
            tmp_pixbuf->save(fname, "png");
            delete tmp_fractal;

            break;
        }
        case (Gtk::RESPONSE_CANCEL):
        {
            _save_img_dlg->hide();
            break;
        }
        default:
        {
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
