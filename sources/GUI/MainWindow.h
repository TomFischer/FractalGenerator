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
 * @file MainWindow.h
 *
 *  Created on: 07/2004
 *      Author: Thomas Fischer
 */

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menu.h>
#include <gtkmm/box.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/notebook.h>

// forward declarations
class ViewerWidget;
class Fractal;

#include <string>
#include <list>

class MainWindow: public Gtk::Window
{
public:
	MainWindow();
	~MainWindow();

public:
	// Methods
	void addViewer(Glib::RefPtr<Gdk::Pixbuf> pixbuf);
	void addFractal(Fractal *fractal);
	void cleanViewerWidgetList();

	// MainWindow interface
protected:
	void dummy();
	void addMandelbrotSet();
	void addJuliaSet();
	void onCreateFarn();
	void onClose();
	void onQuit();
	void history();

	gint delete_event_impl(GdkEventAny*)
	{
		Gtk::Main::quit();
		return 0;
	}

private:
	Gtk::MenuBar main_menu_bar;
	Gtk::Menu fractal_menu;
	Gtk::Menu history_menu;
	Gtk::Menu image_menu;
	Gtk::Notebook notebook;
	Gtk::VBox vbox;

	std::list<ViewerWidget*> vw_list;
};

#endif	//_MAINWINDOW_H_
