/*
* Copyright (C) 2004-2012 Thomas Fischer
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
 * @file MainWindow.cpp
 *
 *  Created on: 07/2004
 *      Author: Thomas Fischer
 */

#include <iostream>

#include "MainWindow.h"
#include "Point.h"
#include "JuliaSet.h"
#include "Farn.h"
#include "ViewerWidget.h"
#include "MandelbrotSetViewerWidget.h"
#include "JuliaSetViewerWidget.h"

#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>

#include <cmath>

MainWindow::MainWindow ()
      : Gtk::Window (Gtk::WINDOW_TOPLEVEL), main_menu_bar (), fractal_menu (),
      history_menu (), image_menu (), vbox (), notebook ()
{
   add ( vbox );

   { //fractal create menu:
      Gtk::Menu::MenuList &menu_list = fractal_menu.items ();
      menu_list.push_back(
         Gtk::Menu_Helpers::MenuElem("Create _Mandelbrot set",
                                     Gtk::AccelKey("<control>m"),
                                     sigc::mem_fun ( *this, &MainWindow::addMandelbrotSet ) ) );

      menu_list.push_back(
         Gtk::Menu_Helpers::MenuElem("Create _Julia set",
                                     Gtk::AccelKey("<control>j"),
                                     sigc::mem_fun (*this, &MainWindow::addJuliaSet) ) );

      menu_list.push_back(
         Gtk::Menu_Helpers::MenuElem("Create _Farn",
                                     Gtk::AccelKey("<control>f"),
                                     sigc::mem_fun (*this, &MainWindow::onCreateFarn) ) );

      menu_list.push_back ( Gtk::Menu_Helpers::SeparatorElem ()	);
      menu_list.push_back(
         Gtk::Menu_Helpers::MenuElem("_Close",
                                     Gtk::AccelKey("<control>c"),
                                     sigc::mem_fun (*this, &MainWindow::onClose) ) );
   }

   // Create the menu bar
   // Gtk::Menu_Helpers::MenuList &main_menu_list = main_menu_bar.items ();
   main_menu_bar.items().push_front(
      Gtk::Menu_Helpers::MenuElem("_Quit",
                                  Gtk::AccelKey("<control>q"),
                                  sigc::mem_fun(*this, &MainWindow::onQuit) ) );

   main_menu_bar.items().push_front(
      Gtk::Menu_Helpers::MenuElem("_Create Fractal",
                                  Gtk::AccelKey ("<alt>c"),
                                  fractal_menu));

   vbox.pack_start ( main_menu_bar, false, false );
   vbox.pack_start ( notebook, false, false );

   const int screen_width(get_screen()->get_width());
   const int screen_height(get_screen()->get_height());

   set_size_request ( 0.7 * screen_width, 0.6 * screen_height );

   show_all ();
}

void MainWindow::dummy ()
{}

void MainWindow::onClose ()
{
   Gtk::Main::quit();
}

void MainWindow::onQuit ()
{
   Gtk::Main::quit();
}

void MainWindow::addMandelbrotSet ()
{
   // spaeter aus dialog auslesen
   double pp0[2] = {-2.0, -2.0}, pp1[2] = {2.0, 2.0};

   Point2D p0 (pp0), p1 (pp1);

   int wnd_w, wnd_h;
   get_size ( wnd_w, wnd_h );
   int quad_size (0.9 * std::min(wnd_w, wnd_h));

   Fractal *fractal (new Apfelmaennchen (p0, p1, quad_size, quad_size, 300));
   vw_list.push_back (new GUI::MandelbrotSetViewerWidget (fractal, *this ));
   std::list<ViewerWidget*>::iterator it (vw_list.end());
   it--;
   std::cout << "notebook: appending page ... " << std::flush;
   notebook.append_page ((*(*it)));
   std::cout << "ok " << std::endl;
   notebook.show_all ();
}

void MainWindow::addFractal ( Fractal *fractal )
{
   vw_list.push_back (new GUI::MandelbrotSetViewerWidget (fractal, *this ));
   std::list<ViewerWidget*>::iterator it (vw_list.end());
   it--;
   std::cout << "notebook: appending page ... " << std::flush;
   notebook.append_page ((*(*it)));
   std::cout << "ok " << std::endl;
   notebook.show_all ();
}

void MainWindow::onCreateFarn()
{
//	double pp0[2] = { -0.5, 0.0 }, pp1[2] = { 0.5, 1.1 };
//	Point2D p0(pp0), p1(pp1);
//
//	int wnd_w, wnd_h;
//	get_size(wnd_w, wnd_h);
//	int quad_size(0.9 * std::min(wnd_w, wnd_h));
//
//	Fractal *fractal(new Farn(quad_size, quad_size, p0, p1));
//	vw_list.push_back(new ViewerWidget(fractal, *this));
//	std::list<ViewerWidget*>::iterator it(vw_list.end());
//	it--;
//	std::cout << "notebook: appending page ... " << std::flush;
//	notebook.append_page((*(*it)));
//	std::cout << "ok " << std::endl;
//	notebook.show_all ();
}


void MainWindow::cleanViewerWidgetList ()
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::addJuliaSet ()
{
   // spaeter aus dialog auslesen
   double pp0[2] = {-0.7, 0.25}, pp1[2] = {2.0, 2.0};
   Point2D p0 (pp0), p1 (pp1);

   int wnd_w, wnd_h;
   get_size ( wnd_w, wnd_h );

   Fractal *fractal (new JuliaSet (p0, p1, 550, 550, 300));
   vw_list.push_back (new GUI::JuliaSetViewerWidget (fractal, *this));
   std::list<ViewerWidget*>::iterator it (vw_list.end());
   it--;
   notebook.append_page ((*(*it)));
   notebook.show_all ();
}

