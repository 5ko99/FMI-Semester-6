# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /var/lib/snapd/snap/clion/145/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/145/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/petko/workspace/FMI-Semester-6/playground/Uno

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/petko/workspace/FMI-Semester-6/playground/Uno/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Uno.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Uno.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Uno.dir/flags.make

CMakeFiles/Uno.dir/CardBody.cpp.o: CMakeFiles/Uno.dir/flags.make
CMakeFiles/Uno.dir/CardBody.cpp.o: ../CardBody.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/playground/Uno/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Uno.dir/CardBody.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Uno.dir/CardBody.cpp.o -c /home/petko/workspace/FMI-Semester-6/playground/Uno/CardBody.cpp

CMakeFiles/Uno.dir/CardBody.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Uno.dir/CardBody.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/playground/Uno/CardBody.cpp > CMakeFiles/Uno.dir/CardBody.cpp.i

CMakeFiles/Uno.dir/CardBody.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Uno.dir/CardBody.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/playground/Uno/CardBody.cpp -o CMakeFiles/Uno.dir/CardBody.cpp.s

CMakeFiles/Uno.dir/Game.cpp.o: CMakeFiles/Uno.dir/flags.make
CMakeFiles/Uno.dir/Game.cpp.o: ../Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/playground/Uno/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Uno.dir/Game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Uno.dir/Game.cpp.o -c /home/petko/workspace/FMI-Semester-6/playground/Uno/Game.cpp

CMakeFiles/Uno.dir/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Uno.dir/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/playground/Uno/Game.cpp > CMakeFiles/Uno.dir/Game.cpp.i

CMakeFiles/Uno.dir/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Uno.dir/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/playground/Uno/Game.cpp -o CMakeFiles/Uno.dir/Game.cpp.s

CMakeFiles/Uno.dir/Player.cpp.o: CMakeFiles/Uno.dir/flags.make
CMakeFiles/Uno.dir/Player.cpp.o: ../Player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/playground/Uno/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Uno.dir/Player.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Uno.dir/Player.cpp.o -c /home/petko/workspace/FMI-Semester-6/playground/Uno/Player.cpp

CMakeFiles/Uno.dir/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Uno.dir/Player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/playground/Uno/Player.cpp > CMakeFiles/Uno.dir/Player.cpp.i

CMakeFiles/Uno.dir/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Uno.dir/Player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/playground/Uno/Player.cpp -o CMakeFiles/Uno.dir/Player.cpp.s

# Object files for target Uno
Uno_OBJECTS = \
"CMakeFiles/Uno.dir/CardBody.cpp.o" \
"CMakeFiles/Uno.dir/Game.cpp.o" \
"CMakeFiles/Uno.dir/Player.cpp.o"

# External object files for target Uno
Uno_EXTERNAL_OBJECTS =

Uno: CMakeFiles/Uno.dir/CardBody.cpp.o
Uno: CMakeFiles/Uno.dir/Game.cpp.o
Uno: CMakeFiles/Uno.dir/Player.cpp.o
Uno: CMakeFiles/Uno.dir/build.make
Uno: CMakeFiles/Uno.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/petko/workspace/FMI-Semester-6/playground/Uno/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Uno"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Uno.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Uno.dir/build: Uno

.PHONY : CMakeFiles/Uno.dir/build

CMakeFiles/Uno.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Uno.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Uno.dir/clean

CMakeFiles/Uno.dir/depend:
	cd /home/petko/workspace/FMI-Semester-6/playground/Uno/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/petko/workspace/FMI-Semester-6/playground/Uno /home/petko/workspace/FMI-Semester-6/playground/Uno /home/petko/workspace/FMI-Semester-6/playground/Uno/cmake-build-debug /home/petko/workspace/FMI-Semester-6/playground/Uno/cmake-build-debug /home/petko/workspace/FMI-Semester-6/playground/Uno/cmake-build-debug/CMakeFiles/Uno.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Uno.dir/depend

