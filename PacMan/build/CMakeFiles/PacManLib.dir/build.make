# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/runner/work/PMSwEng/PMSwEng/PacMan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/runner/work/PMSwEng/PMSwEng/PacMan/build

# Include any dependencies generated for this target.
include CMakeFiles/PacManLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PacManLib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PacManLib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PacManLib.dir/flags.make

CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.o: CMakeFiles/PacManLib.dir/flags.make
CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.o: PacManLib_autogen/mocs_compilation.cpp
CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.o: CMakeFiles/PacManLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runner/work/PMSwEng/PMSwEng/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.o -MF CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.o -c /home/runner/work/PMSwEng/PMSwEng/PacMan/build/PacManLib_autogen/mocs_compilation.cpp

CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/PMSwEng/PMSwEng/PacMan/build/PacManLib_autogen/mocs_compilation.cpp > CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.i

CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/PMSwEng/PMSwEng/PacMan/build/PacManLib_autogen/mocs_compilation.cpp -o CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.s

CMakeFiles/PacManLib.dir/pacman.cpp.o: CMakeFiles/PacManLib.dir/flags.make
CMakeFiles/PacManLib.dir/pacman.cpp.o: /home/runner/work/PMSwEng/PMSwEng/PacMan/pacman.cpp
CMakeFiles/PacManLib.dir/pacman.cpp.o: CMakeFiles/PacManLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runner/work/PMSwEng/PMSwEng/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PacManLib.dir/pacman.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PacManLib.dir/pacman.cpp.o -MF CMakeFiles/PacManLib.dir/pacman.cpp.o.d -o CMakeFiles/PacManLib.dir/pacman.cpp.o -c /home/runner/work/PMSwEng/PMSwEng/PacMan/pacman.cpp

CMakeFiles/PacManLib.dir/pacman.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PacManLib.dir/pacman.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/PMSwEng/PMSwEng/PacMan/pacman.cpp > CMakeFiles/PacManLib.dir/pacman.cpp.i

CMakeFiles/PacManLib.dir/pacman.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PacManLib.dir/pacman.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/PMSwEng/PMSwEng/PacMan/pacman.cpp -o CMakeFiles/PacManLib.dir/pacman.cpp.s

CMakeFiles/PacManLib.dir/player.cpp.o: CMakeFiles/PacManLib.dir/flags.make
CMakeFiles/PacManLib.dir/player.cpp.o: /home/runner/work/PMSwEng/PMSwEng/PacMan/player.cpp
CMakeFiles/PacManLib.dir/player.cpp.o: CMakeFiles/PacManLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runner/work/PMSwEng/PMSwEng/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PacManLib.dir/player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PacManLib.dir/player.cpp.o -MF CMakeFiles/PacManLib.dir/player.cpp.o.d -o CMakeFiles/PacManLib.dir/player.cpp.o -c /home/runner/work/PMSwEng/PMSwEng/PacMan/player.cpp

CMakeFiles/PacManLib.dir/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PacManLib.dir/player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/PMSwEng/PMSwEng/PacMan/player.cpp > CMakeFiles/PacManLib.dir/player.cpp.i

CMakeFiles/PacManLib.dir/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PacManLib.dir/player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/PMSwEng/PMSwEng/PacMan/player.cpp -o CMakeFiles/PacManLib.dir/player.cpp.s

CMakeFiles/PacManLib.dir/ghost.cpp.o: CMakeFiles/PacManLib.dir/flags.make
CMakeFiles/PacManLib.dir/ghost.cpp.o: /home/runner/work/PMSwEng/PMSwEng/PacMan/ghost.cpp
CMakeFiles/PacManLib.dir/ghost.cpp.o: CMakeFiles/PacManLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runner/work/PMSwEng/PMSwEng/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PacManLib.dir/ghost.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PacManLib.dir/ghost.cpp.o -MF CMakeFiles/PacManLib.dir/ghost.cpp.o.d -o CMakeFiles/PacManLib.dir/ghost.cpp.o -c /home/runner/work/PMSwEng/PMSwEng/PacMan/ghost.cpp

CMakeFiles/PacManLib.dir/ghost.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PacManLib.dir/ghost.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/PMSwEng/PMSwEng/PacMan/ghost.cpp > CMakeFiles/PacManLib.dir/ghost.cpp.i

CMakeFiles/PacManLib.dir/ghost.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PacManLib.dir/ghost.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/PMSwEng/PMSwEng/PacMan/ghost.cpp -o CMakeFiles/PacManLib.dir/ghost.cpp.s

CMakeFiles/PacManLib.dir/maze.cpp.o: CMakeFiles/PacManLib.dir/flags.make
CMakeFiles/PacManLib.dir/maze.cpp.o: /home/runner/work/PMSwEng/PMSwEng/PacMan/maze.cpp
CMakeFiles/PacManLib.dir/maze.cpp.o: CMakeFiles/PacManLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runner/work/PMSwEng/PMSwEng/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PacManLib.dir/maze.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PacManLib.dir/maze.cpp.o -MF CMakeFiles/PacManLib.dir/maze.cpp.o.d -o CMakeFiles/PacManLib.dir/maze.cpp.o -c /home/runner/work/PMSwEng/PMSwEng/PacMan/maze.cpp

CMakeFiles/PacManLib.dir/maze.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PacManLib.dir/maze.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/PMSwEng/PMSwEng/PacMan/maze.cpp > CMakeFiles/PacManLib.dir/maze.cpp.i

CMakeFiles/PacManLib.dir/maze.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PacManLib.dir/maze.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/PMSwEng/PMSwEng/PacMan/maze.cpp -o CMakeFiles/PacManLib.dir/maze.cpp.s

CMakeFiles/PacManLib.dir/Test.cpp.o: CMakeFiles/PacManLib.dir/flags.make
CMakeFiles/PacManLib.dir/Test.cpp.o: /home/runner/work/PMSwEng/PMSwEng/PacMan/Test.cpp
CMakeFiles/PacManLib.dir/Test.cpp.o: CMakeFiles/PacManLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/runner/work/PMSwEng/PMSwEng/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/PacManLib.dir/Test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PacManLib.dir/Test.cpp.o -MF CMakeFiles/PacManLib.dir/Test.cpp.o.d -o CMakeFiles/PacManLib.dir/Test.cpp.o -c /home/runner/work/PMSwEng/PMSwEng/PacMan/Test.cpp

CMakeFiles/PacManLib.dir/Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/PacManLib.dir/Test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/runner/work/PMSwEng/PMSwEng/PacMan/Test.cpp > CMakeFiles/PacManLib.dir/Test.cpp.i

CMakeFiles/PacManLib.dir/Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/PacManLib.dir/Test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/runner/work/PMSwEng/PMSwEng/PacMan/Test.cpp -o CMakeFiles/PacManLib.dir/Test.cpp.s

# Object files for target PacManLib
PacManLib_OBJECTS = \
"CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/PacManLib.dir/pacman.cpp.o" \
"CMakeFiles/PacManLib.dir/player.cpp.o" \
"CMakeFiles/PacManLib.dir/ghost.cpp.o" \
"CMakeFiles/PacManLib.dir/maze.cpp.o" \
"CMakeFiles/PacManLib.dir/Test.cpp.o"

# External object files for target PacManLib
PacManLib_EXTERNAL_OBJECTS =

libPacManLib.so: CMakeFiles/PacManLib.dir/PacManLib_autogen/mocs_compilation.cpp.o
libPacManLib.so: CMakeFiles/PacManLib.dir/pacman.cpp.o
libPacManLib.so: CMakeFiles/PacManLib.dir/player.cpp.o
libPacManLib.so: CMakeFiles/PacManLib.dir/ghost.cpp.o
libPacManLib.so: CMakeFiles/PacManLib.dir/maze.cpp.o
libPacManLib.so: CMakeFiles/PacManLib.dir/Test.cpp.o
libPacManLib.so: CMakeFiles/PacManLib.dir/build.make
libPacManLib.so: /home/runner/work/PMSwEng/Qt/5.15.2/gcc_64/lib/libQt5Widgets.so.5.15.2
libPacManLib.so: /home/runner/work/PMSwEng/Qt/5.15.2/gcc_64/lib/libQt5Gui.so.5.15.2
libPacManLib.so: /home/runner/work/PMSwEng/Qt/5.15.2/gcc_64/lib/libQt5Core.so.5.15.2
libPacManLib.so: CMakeFiles/PacManLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/runner/work/PMSwEng/PMSwEng/PacMan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX shared library libPacManLib.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PacManLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PacManLib.dir/build: libPacManLib.so
.PHONY : CMakeFiles/PacManLib.dir/build

CMakeFiles/PacManLib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PacManLib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PacManLib.dir/clean

CMakeFiles/PacManLib.dir/depend:
	cd /home/runner/work/PMSwEng/PMSwEng/PacMan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runner/work/PMSwEng/PMSwEng/PacMan /home/runner/work/PMSwEng/PMSwEng/PacMan /home/runner/work/PMSwEng/PMSwEng/PacMan/build /home/runner/work/PMSwEng/PMSwEng/PacMan/build /home/runner/work/PMSwEng/PMSwEng/PacMan/build/CMakeFiles/PacManLib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/PacManLib.dir/depend

