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
CMAKE_COMMAND = /var/lib/snapd/snap/clion/139/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/139/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/petko/workspace/playground/solutionTesting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/petko/workspace/playground/solutionTesting/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/solutionTesting.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/solutionTesting.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/solutionTesting.dir/flags.make

CMakeFiles/solutionTesting.dir/main.cpp.o: CMakeFiles/solutionTesting.dir/flags.make
CMakeFiles/solutionTesting.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/playground/solutionTesting/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/solutionTesting.dir/main.cpp.o"
	/usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/solutionTesting.dir/main.cpp.o -c /home/petko/workspace/playground/solutionTesting/main.cpp

CMakeFiles/solutionTesting.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/solutionTesting.dir/main.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/playground/solutionTesting/main.cpp > CMakeFiles/solutionTesting.dir/main.cpp.i

CMakeFiles/solutionTesting.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/solutionTesting.dir/main.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/playground/solutionTesting/main.cpp -o CMakeFiles/solutionTesting.dir/main.cpp.s

# Object files for target solutionTesting
solutionTesting_OBJECTS = \
"CMakeFiles/solutionTesting.dir/main.cpp.o"

# External object files for target solutionTesting
solutionTesting_EXTERNAL_OBJECTS =

solutionTesting: CMakeFiles/solutionTesting.dir/main.cpp.o
solutionTesting: CMakeFiles/solutionTesting.dir/build.make
solutionTesting: CMakeFiles/solutionTesting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/petko/workspace/playground/solutionTesting/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable solutionTesting"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/solutionTesting.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/solutionTesting.dir/build: solutionTesting

.PHONY : CMakeFiles/solutionTesting.dir/build

CMakeFiles/solutionTesting.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/solutionTesting.dir/cmake_clean.cmake
.PHONY : CMakeFiles/solutionTesting.dir/clean

CMakeFiles/solutionTesting.dir/depend:
	cd /home/petko/workspace/playground/solutionTesting/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/petko/workspace/playground/solutionTesting /home/petko/workspace/playground/solutionTesting /home/petko/workspace/playground/solutionTesting/cmake-build-debug /home/petko/workspace/playground/solutionTesting/cmake-build-debug /home/petko/workspace/playground/solutionTesting/cmake-build-debug/CMakeFiles/solutionTesting.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/solutionTesting.dir/depend

