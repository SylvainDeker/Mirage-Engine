project(Mirage-Engine)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)



SET(mirageengine
    src/main.cpp
    src/qt/MainWindow.cpp
    src/qt/MainWindow.hpp
    src/qt/MainWindow.ui
)

add_executable(mirage ${mirageengine})
target_link_libraries(mirage Qt5::Widgets)
