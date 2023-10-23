cmake_minimum_required(VERSION 3.5)
project(PacMan VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

enable_testing()

set(PROJECT_SOURCES
    main.cpp
)

add_library(LocalLib SHARED
    MyWidget.h MyWidget.cpp
)
target_link_libraries(LocalLib Qt${QT_VERSION_MAJOR}::Widgets)

add_library(PacManLib SHARED
    pacman.h pacman.cpp
    player.h player.cpp
    ghost.h ghost.cpp
    maze.h maze.cpp
    Test.h Test.cpp
)
target_link_libraries(PacManLib Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(PacMan main.cpp)
target_link_libraries(PacMan LocalLib PacManLib)

add_subdirectory(Tests)
