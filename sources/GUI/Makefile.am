## Makefile.am

INCLUDES = $(GTKMM_CFLAGS)

bin_PROGRAMS = fractalgenerator
fractalgenerator_SOURCES = main.cc MainWindow.cc \
	ApfelmaennchenWidget.cc  JuliaSetWidget.cc \
	ViewerWidget.cc CoordinateInputDlgHelper.cc PointInputDlg.cc \
	fractal.cc apfelmaennchen.cc JuliaSet.cc Canvas.cc farn.cc 
fractalgenerator_LDADD = $(GTKMM_LIBS)
