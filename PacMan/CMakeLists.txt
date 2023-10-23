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

<<<<<<< HEAD
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PacMan
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        pacman.h pacman.cpp
        player.h player.cpp
        ghost.h ghost.cpp
        maze.h maze.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PacMan APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PacMan SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PacMan
            ${PROJECT_SOURCES}
        )
    endif()
endif()
=======
add_library(LocalLib SHARED
    mainwindow.cpp mainwindow.h mainwindow.ui
)
target_link_libraries(LocalLib Qt${QT_VERSION_MAJOR}::Widgets)
>>>>>>> 5ea2a3e2fbe82015654bed085e9305cae02db3fb

add_library(PacManLib SHARED
    Test.cpp
    Test.h
)

add_executable(PacMan main.cpp)
target_link_libraries(PacMan LocalLib PacManLib)

add_subdirectory(Tests)
