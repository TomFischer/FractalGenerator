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

ViewerWidget::ViewerWidget ( Fractal *afractal, MainWindow &aparent,
                             unsigned type )
      : Gtk::VBox (), parent ( aparent ),
      hbox (), fractal ( afractal ), canvas ( NULL ),
      mbs_wdgt (NULL), js_wdgt (NULL),
      save_img_dlg (new Gtk::FileChooserDialog ( "Save fractal", Gtk::FILE_CHOOSER_ACTION_SAVE )),
      tof (type)
{
   if (tof == 0) mbs_wdgt = new ApfelmaennchenWidget ( *this );
   else js_wdgt = new JuliaSetWidget (*this);

   // make pixbuf from fractal
   Glib::RefPtr <Gdk::Pixbuf> pixbuf (Gdk::Pixbuf::create_from_data
		(getData (*fractal), Gdk::COLORSPACE_RGB, false, 8, fractal->getCols(),
		fractal->getRows (), fractal->getCols() * 3));

   // create with this pixbuf a Canvas
   canvas = new Canvas ( pixbuf, *this );

   // add these Canvas to this widget
   hbox.pack_start ( *canvas, Gtk::PACK_SHRINK );

   // make and add controls for fractal
   if (tof == 0) hbox.pack_start(*mbs_wdgt, Gtk::PACK_EXPAND_PADDING );
   else hbox.pack_start(*js_wdgt, Gtk::PACK_EXPAND_PADDING );

   pack_start (hbox, Gtk::PACK_SHRINK);

   save_img_dlg->add_button("Cancel", Gtk::RESPONSE_CANCEL);
   save_img_dlg->add_button("Ok", Gtk::RESPONSE_OK);
}

ViewerWidget::~ViewerWidget()
{
   if (fractal) delete fractal;
   delete canvas;
   if (mbs_wdgt) delete mbs_wdgt;
   //if (js_wdgt) delete js_wdgt;
   delete save_img_dlg;
}

guint8* ViewerWidget::getData(Fractal const& input_fractal)
{
	size_t rows(input_fractal.getRows()), cols(input_fractal.getCols());
	size_t nob(3); // number of bytes
	guint8* data(new guint8[nob * rows * cols]);

	unsigned max(input_fractal.getMaxVal()), min(input_fractal.getMinVal());
//	gushort sred, ered, sgreen, egreen, sblue, eblue;
//	if (tof == 0) {
//		Gdk::Color c0(mbs_wdgt->getColor(true));
//		Gdk::Color c1(mbs_wdgt->getColor(false));
//		sred = c0.get_red();
//		ered = c1.get_red();
//		sgreen = c0.get_green();
//		egreen = c1.get_green();
//		sblue = c0.get_blue();
//		eblue = c1.get_blue();
//	}

	// parameters of HSV color space
	double max_hue(240);
	double saturation(0.7);
	double value(0.7);

	// color transformation
//	double dred(ered - sred), dgreen(egreen - sgreen), dblue(eblue - sblue);
	double dfrac(max_hue);
	if (max != min)
		dfrac /= (max-min);

	for (size_t r = 0; r < rows; ++r) {
		for (size_t c = 0; c < cols; ++c) {

			double hue (static_cast<double> ((input_fractal(r, c) - min) * dfrac));

			// helper for transformation to RGB
			size_t h_i (static_cast<size_t>(floor(hue / 60)));
			double f (hue/60 - h_i);
			double p (value * (1 - saturation));
			double q (value * (1 - saturation * f));
			double t (value * (1 - saturation * (1 - f)));

			// store data in RGB
			size_t idx((r * cols + c) * nob);
			switch (h_i) {
			case 0:
				data[idx] = static_cast<guint8> (value * 255);
				data[idx + 1] = static_cast<guint8> (t * 255);
				data[idx + 2] = static_cast<guint8> (p * 255);
				break;
			case 1:
				data[idx] = static_cast<guint8> (q * 255);
				data[idx + 1] = static_cast<guint8> (value * 255);
				data[idx + 2] = static_cast<guint8> (p * 255);
				break;
			case 2:
				data[idx] = static_cast<guint8> (p * 255);
				data[idx + 1] = static_cast<guint8> (value * 255);
				data[idx + 2] = static_cast<guint8> (t * 255);
				break;
			case 3:
				data[idx] = static_cast<guint8> (p * 255);
				data[idx + 1] = static_cast<guint8> (q * 255);
				data[idx + 2] = static_cast<guint8> (value * 255);
				break;
			case 4:
				data[idx] = static_cast<guint8> (t * 255);
				data[idx + 1] = static_cast<guint8> (p * 255);
				data[idx + 2] = static_cast<guint8> (value * 255);
				break;
			case 5:
				data[idx] = static_cast<guint8> (value * 255);
				data[idx + 1] = static_cast<guint8> (p * 255);
				data[idx + 2] = static_cast<guint8> (q * 255);
				break;
			case 6:
				data[idx] = static_cast<guint8> (value * 255);
				data[idx + 1] = static_cast<guint8> (t * 255);
				data[idx + 2] = static_cast<guint8> (p * 255);
				break;
			default:
				std::cout << "error computing color value for pixel (" << r << "," << c << "): " << input_fractal(r, c) << ", h_i: " << h_i << std::endl;
			} // end switch

//			data[idx] = static_cast<guint8> ((sred + frac_val * dred) / 65535 * 255);
//			data[idx + 1] = static_cast<guint8> ((sgreen + frac_val * dgreen) / 65535 * 255);
//			data[idx + 2] = static_cast<guint8> ((sblue + frac_val * dblue) / 65535 * 255);
		}
	}

	return data;
}

void ViewerWidget::onSaveImg()
{
	int res = save_img_dlg->run();

	switch (res) {
	case (Gtk::RESPONSE_OK): {
		save_img_dlg->hide();
		std::string fname(save_img_dlg->get_filename());

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

		Gtk::Image const& img (canvas->getImage());
//		Glib::RefPtr<const Gdk::Pixbuf> pix_buf (img.get_pixbuf());
		Glib::RefPtr<Gdk::Pixbuf>::cast_const (img.get_pixbuf())->save(fname, "png");
		break;
	}
	case (Gtk::RESPONSE_CANCEL): {
		save_img_dlg->hide();
		break;
	}
	default: {
		std::cout << "Unexpected button clicked." << std::endl;
		break;
	}
	}
}

void ViewerWidget::onMovie ()
{
	Point2D p0 (mbs_wdgt->getPoint (0));
   //Point <double, 2> p1 (mbs_wdgt->getPoint (0));
   Point2D temp1;
   Point2D temp2;
   temp1.setCoordinate(0, 2);
   temp1.setCoordinate(1, 2);
   temp2.setCoordinate(0, -2);
   temp2.setCoordinate(1, -2);
   size_t res (mbs_wdgt->getIterationDepth ());
   size_t size (mbs_wdgt->getSize ());
   // create a new Fractal
   Fractal *tf (fractal);
   fractal = new Apfelmaennchen (temp2, temp1, size, size, res);
   // make pixbuf from fractal
   Glib::RefPtr <Gdk::Pixbuf> pixbuf (Gdk::Pixbuf::create_from_data
		(getData (*fractal), Gdk::COLORSPACE_RGB, false, 8, fractal->getCols(),
		fractal->getRows (), fractal->getCols() * 3));

   for (unsigned i=0; i<500; i++) {
      // save Image
      std::string fname ("pictures/dump");
      if (i < 10) fname += "00";
      else if (i < 100) fname += "0";
      char txt[255];
      sprintf( txt, "%d", i );
      fname += txt;
      fname += ".jpg";

      temp1.setCoordinate(0, 24*temp1[0]/25.0 + p0[0]/25.0);
      temp1.setCoordinate(1, 24*temp1[1]/25.0 + p0[1]/25.0);
      temp2.setCoordinate(0, 24*temp2[0]/25.0 + p0[0]/25.0);
      temp2.setCoordinate(1, 24*temp2[1]/25.0 + p0[1]/25.0);
      // create a new Fractal
      Fractal *tf1 (new Apfelmaennchen (temp2, temp1, size, size, res));
      swap (tf1, fractal);
      delete tf1;
      // make pixbuf from fractal

      guint8* data (getData(*fractal));
      Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data
                                         (data, Gdk::COLORSPACE_RGB, false, 8, fractal->getCols(),
                                          fractal->getRows (), fractal->getCols() * 3);

      std::cout << "saving " << fname << " ... " << std::flush;
      try {
         pixbuf->save (fname, "jpeg");
      } catch ( Glib::FileError ) {
         std::cout << "Fehler beim Speichern in Datei " << fname << std::endl;
      } catch ( Gdk::PixbufError ) {
         std::cout << "Fehler Gdk::PixbufError " << std::endl;
      }
      std::cout << "done " << std::endl;
      delete [] data;
   }
   fractal = tf;
}

void ViewerWidget::onNewViewerWidget ()
{
   if (tof == 0) {
	   Point2D p0 (mbs_wdgt->getPoint (0));
	   Point2D p1 (mbs_wdgt->getPoint (1));
      size_t res (mbs_wdgt->getIterationDepth ());
      size_t size (mbs_wdgt->getSize ());

      Apfelmaennchen *fractal (new Apfelmaennchen (p0, p1, size, size, res));
      parent.addFractal (fractal);
   } else {
	   Point2D p0 (js_wdgt->getPoint (0));
	   Point2D p1 (js_wdgt->getPoint (1));
      size_t res (js_wdgt->getIterationDepth ());
      size_t size (js_wdgt->getSize ());

      JuliaSet *fractal (new JuliaSet (p0, p1, size, size, res));
      parent.addFractal (fractal);
   }
}

void ViewerWidget::onNewFractal()
{
	Point2D p0(mbs_wdgt->getPoint(0));
	Point2D p1(mbs_wdgt->getPoint(1));
	size_t res(mbs_wdgt->getIterationDepth());
	size_t size(mbs_wdgt->getSize());

	// create a new Fractal
	fractal = new Apfelmaennchen(p0, p1, size, size, res);
	// make pixbuf from fractal
	Glib::RefPtr<Gdk::Pixbuf> pixbuf(Gdk::Pixbuf::create_from_data(getData(
			*fractal), Gdk::COLORSPACE_RGB, false, 8, fractal->getCols(),
			fractal->getRows(), fractal->getCols() * 3));
	// give the pixbuf to the Canvas
	canvas->setImage(pixbuf);
	// update the FractalWidget
	if (tof == 0)
		mbs_wdgt->update();
	show_all();
}

Fractal* ViewerWidget::getFractal ()
{
   return fractal;
}

ApfelmaennchenWidget* ViewerWidget::getApfelmaennchenWidget ()
{
   return mbs_wdgt;
}

JuliaSetWidget* ViewerWidget::getJuliaSetWidget ()
{
   return js_wdgt;
}

bool ViewerWidget::onMotionNotifyEvent ( GdkEventMotion *event )
{
   return canvas->onMotionNotifyEvent ( event );
}

Canvas const* ViewerWidget::getCanvas () const
{
   return canvas;
}
