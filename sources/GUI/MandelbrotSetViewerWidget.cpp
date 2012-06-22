/*
* Copyright (C) 2012 Thomas Fischer
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
 * @file MandelbrotSetViewerWidget.cpp
 *
 *  Created on: 21.06.2012
 *      Author: Thomas Fischer
 */

#include <limits>

#include "lexical_cast.h"
#include "MandelbrotSetViewerWidget.h"

namespace GUI {

MandelbrotSetViewerWidget::MandelbrotSetViewerWidget(Fractal *fractal,
		MainWindow &parent) :
	ViewerWidget(fractal, parent), _mbs_wdgt(new ApfelmaennchenWidget(*this))
{
	// create pixbuf from fractal
	Glib::RefPtr<Gdk::Pixbuf> pixbuf(Gdk::Pixbuf::create_from_data(getData(
			*fractal), Gdk::COLORSPACE_RGB, false, 8, fractal->getCols(),
			fractal->getRows(), fractal->getCols() * 3));

	// create with this pixbuf a Canvas
	_canvas = new Canvas(pixbuf, *this);

	// add the Canvas to this widget
	_hbox.pack_start(*_canvas, Gtk::PACK_SHRINK);
	// make and add controls for fractal
	_hbox.pack_start(*_mbs_wdgt, Gtk::PACK_EXPAND_PADDING);

	pack_start(_hbox, Gtk::PACK_SHRINK);

	_save_img_dlg->add_button("Cancel", Gtk::RESPONSE_CANCEL);
	_save_img_dlg->add_button("Ok", Gtk::RESPONSE_OK);
}

MandelbrotSetViewerWidget::~MandelbrotSetViewerWidget()
{
	delete _mbs_wdgt;
}

guint8* MandelbrotSetViewerWidget::getData(Fractal const& input_fractal) const
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

void MandelbrotSetViewerWidget::onMovie ()
{
	Point2D p0 (_mbs_wdgt->getPoint (0));
   //Point <double, 2> p1 (mbs_wdgt->getPoint (0));
   Point2D temp1;
   Point2D temp2;
   temp1.setCoordinate(0, 2);
   temp1.setCoordinate(1, 2);
   temp2.setCoordinate(0, -2);
   temp2.setCoordinate(1, -2);
   size_t res (_mbs_wdgt->getIterationDepth ());
   size_t size (_mbs_wdgt->getSize ());
   // create a new Fractal
   Fractal *tf (_fractal);
   _fractal = new Apfelmaennchen (temp2, temp1, size, size, res);
   // make pixbuf from fractal
   Glib::RefPtr <Gdk::Pixbuf> pixbuf (Gdk::Pixbuf::create_from_data
		(getData (*_fractal), Gdk::COLORSPACE_RGB, false, 8, _fractal->getCols(),
		_fractal->getRows (), _fractal->getCols() * 3));

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
      std::swap (tf1, _fractal);
      delete tf1;
      // make pixbuf from fractal

      guint8* data (getData(*_fractal));
      Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_data
                                         (data, Gdk::COLORSPACE_RGB, false, 8, _fractal->getCols(),
                                          _fractal->getRows (), _fractal->getCols() * 3);

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
   _fractal = tf;
}

void MandelbrotSetViewerWidget::onNewViewerWidget()
{
	Point2D p0(_mbs_wdgt->getPoint(0));
	Point2D p1(_mbs_wdgt->getPoint(1));
	size_t res(_mbs_wdgt->getIterationDepth());
	size_t size(_mbs_wdgt->getSize());

	// make p0 left point
	if (p1[0] < p0[0]) std::swap (p0[0], p1[0]);
	// make p0 lower point
	if (p0[1] > p1[1]) std::swap (p0[1], p1[1]);

	// move p1 such that p0 and p1 describes a square
	if (fabs ((p1[0] - p0[0]) - (p1[1] - p0[0])) < std::numeric_limits<float>::epsilon()) {
		const double max_dist (std::max (p1[0] - p0[0], p1[1] - p0[1]));
		p1[0] = p0[0] + max_dist;
		p1[1] = p0[1] + max_dist;
	}

	_mbs_wdgt->getPointInputDlg(0).setCoordinate(0, p0[0]);
	_mbs_wdgt->getPointInputDlg(0).setCoordinate(1, p0[1]);
	_mbs_wdgt->getPointInputDlg(1).setCoordinate(0, p1[0]);
	_mbs_wdgt->getPointInputDlg(1).setCoordinate(1, p1[1]);

	Apfelmaennchen *fractal(new Apfelmaennchen(p0, p1, size, size, res));
	_parent.addFractal(fractal);
}

void MandelbrotSetViewerWidget::onNewFractal()
{
	Point2D const& p0(_mbs_wdgt->getPoint(0));
	Point2D const& p1(_mbs_wdgt->getPoint(1));
	size_t res(_mbs_wdgt->getIterationDepth());
	size_t size(_mbs_wdgt->getSize());

	// create a new Fractal
	delete _fractal;
	_fractal = new Apfelmaennchen(p0, p1, size, size, res);
	// make pixbuf from fractal
	Glib::RefPtr<Gdk::Pixbuf> pixbuf(Gdk::Pixbuf::create_from_data(getData(
			*_fractal), Gdk::COLORSPACE_RGB, false, 8, _fractal->getCols(),
			_fractal->getRows(), _fractal->getCols() * 3));
	// give the pixbuf to the Canvas
	_canvas->setImage(pixbuf);
	// update the FractalWidget
	_mbs_wdgt->update();
	show_all();
}

bool MandelbrotSetViewerWidget::processMotionNotifyEvent(GdkEventMotion *event)
{
	const unsigned x(lexical_cast<unsigned> (event->x));
	const unsigned y(lexical_cast<unsigned> (event->y));
	_mbs_wdgt->actualizePointerPosition(x, y);
	return true;
}

bool MandelbrotSetViewerWidget::processButtonPressEvent ( GdkEventButton *event )
{
   const unsigned x0(lexical_cast <unsigned> (event->x));
   const unsigned y0(lexical_cast <unsigned> (event->y));
   _mbs_wdgt->onCoordinateChanged (0, x0, y0);
   return true;
}

bool MandelbrotSetViewerWidget::processButtonReleaseEvent(GdkEventButton *event)
{
	unsigned x(lexical_cast<unsigned> (event->x));
	unsigned y(lexical_cast<unsigned> (event->y));

	// fetch coords of p0
	Point2D p0(_mbs_wdgt->getPoint(0));

	unsigned mid = unsigned(0.5 * (abs(x - p0[0]) + abs(y - p0[1])));
	unsigned temp;
	if (p0[0] < x)
		x = p0[0] + mid;
	else {
		temp = p0[0] - mid;
		x = p0[0];
		p0[0] = temp;
	}
	if (p0[1] < y)
		y = p0[1] + mid;
	else {
		temp = p0[1] - mid;
		y = p0[1];
		p0[1] = temp;
	}

	_mbs_wdgt->onCoordinateChanged(1, x, y);

	return true;
}

} // end namespace GUI
