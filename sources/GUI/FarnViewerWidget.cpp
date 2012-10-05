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
 * @file FarnViewerWidget.cpp
 */

#include <FarnViewerWidget.h>

namespace GUI {

FarnViewerWidget::FarnViewerWidget(Fractal *fractal, MainWindow &parent) :
		ViewerWidget(fractal, parent)
{
	// create pixbuf from fractal
	Glib::RefPtr<Gdk::Pixbuf> pixbuf(Gdk::Pixbuf::create_from_data(getData(
			*fractal), Gdk::COLORSPACE_RGB, false, 8, fractal->getCols(),
			fractal->getRows(), fractal->getCols() * 3));

	// create with this pixbuf a Canvas
	_canvas = new Canvas(pixbuf, *this);
	_canvas->set_size_request (fractal->getCols(), fractal->getRows());

	// add the Canvas to this widget
	_hbox.pack_start(*_canvas, Gtk::PACK_EXPAND_PADDING);

	pack_start(_hbox, Gtk::PACK_SHRINK);

	_save_img_dlg->add_button("Cancel", Gtk::RESPONSE_CANCEL);
	_save_img_dlg->add_button("Ok", Gtk::RESPONSE_OK);
}

FarnViewerWidget::~FarnViewerWidget()
{
}

void FarnViewerWidget::onMovie ()
{}

void FarnViewerWidget::onNewViewerWidget()
{}

void FarnViewerWidget::onNewFractal ()
{}

bool FarnViewerWidget::processMotionNotifyEvent(GdkEventMotion *event)
{
	return true;
}

bool FarnViewerWidget::processButtonPressEvent(GdkEventButton *event)
{
	return true;
}

bool FarnViewerWidget::processButtonReleaseEvent(GdkEventButton *event)
{
	return true;
}


guint8* FarnViewerWidget::getData(Fractal const& input_fractal) const
{
	size_t rows(input_fractal.getRows()), cols(input_fractal.getCols());
	size_t nob(3); // number of bytes
	guint8* data(new guint8[nob * rows * cols]);

	unsigned max(input_fractal.getMaxVal()), min(input_fractal.getMinVal());

	// parameters of HSV color space
	double max_hue(240);
	double saturation(0.8);
	double value(0.5);

	// color transformation
	double dfrac(max_hue);
	if (max != min)
		dfrac /= (max-min);

	for (size_t r = 0; r < rows; ++r) {
		for (size_t c = 0; c < cols; ++c) {

			double hue (static_cast<double> ((input_fractal(r, c) - min) * dfrac));

			// helpers for transformation to RGB
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
		}
	}
	return data;
}

} // end namespace GUI
