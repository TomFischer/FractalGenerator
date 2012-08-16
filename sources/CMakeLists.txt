CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT (FractalGenerator)

### CMake includes ###
INCLUDE(scripts/cmake/Functions.cmake)

FIND_PACKAGE(PkgConfig)

SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )

PKG_CHECK_MODULES(GTKMM gtkmm-2.4)

# Add subdirectories with the projects
ADD_SUBDIRECTORY( GUI )

INCLUDE_DIRECTORIES(
        .
        ${GTKMM_INCLUDE_DIRS}
        ./GUI/
)

# Create the executable
ADD_EXECUTABLE( FractalGenerator
        main.cpp
        ${SOURCES}
        ${HEADERS}
)

TARGET_LINK_LIBRARIES ( FractalGenerator
        GUI
        ${GTKMM_LIBRARIES}
)

ADD_EXECUTABLE( DrawingAreaTest
        DrawingAreaTest.cpp
        ${SOURCES}
        ${HEADERS}
)

TARGET_LINK_LIBRARIES ( DrawingAreaTest 
        GUI
        ${GTKMM_LIBRARIES}
)

