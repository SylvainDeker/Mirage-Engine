project(Mirage-Engine)
cmake_minimum_required(VERSION 3.11.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS OpenGL REQUIRED )

find_package(OpenGL REQUIRED )


SET(mirageengine
    src/main.cpp
    src/qt/MainGLWidget.cpp
    src/qt/MainGLWidget.hpp
    src/qt/MainWindow.ui
    src/qt/MainWindow.cpp
    src/qt/MainWindow.hpp
)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
add_executable(mirage ${mirageengine})
target_link_libraries(mirage Qt5::Widgets ${OPENGL_LIBRARIES})
