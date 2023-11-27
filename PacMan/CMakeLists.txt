cmake_minimum_required(VERSION 3.5)
project(PacMan VERSION 0.1 LANGUAGES CXX)

# CMake Parameters
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Enable Project-wide Testing
enable_testing()

# Add Project sources
set(PROJECT_SOURCES
    main.cpp
)

# Add library for Qt Functionality
add_library(LocalLib SHARED
    locallib_global.h       # Global file to set compile declarations
    mywidget.h mywidget.cpp # Detect Key Presses
)
target_link_libraries(LocalLib Qt6::Widgets)

# Add PacMan game Library
add_library(PacManLib SHARED
    pacmanlib_global.h  # Global file to set compile declarations -> https://doc.qt.io/qt-5/sharedlibrary.html
    pacman.h pacman.cpp # Main Game Class
    player.h player.cpp # Player movement
    ghost.h ghost.cpp   # Ghost behaviour
    maze.h maze.cpp     # Possible Movement directions and available food
    Test.h Test.cpp     # Example class for Test
    ResourceSystem.qrc
)
target_link_libraries(PacManLib Qt6::Widgets)

# Set LIBDEF
set(LIBDEF "COMPILE_LIBRARY")
target_compile_definitions(LocalLib PRIVATE ${LIBDEF})
target_compile_definitions(PacManLib PRIVATE ${LIBDEF})

# Create Main Executable
add_executable(PacMan main.cpp)
target_link_libraries(PacMan LocalLib PacManLib)

# Add Tests
add_subdirectory(Tests)
