# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /var/lib/snapd/snap/clion/149/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/149/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/petko/workspace/FMI-Semester-6/8Puzzle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/8Puzzle.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/8Puzzle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/8Puzzle.dir/flags.make

CMakeFiles/8Puzzle.dir/main.cpp.o: CMakeFiles/8Puzzle.dir/flags.make
CMakeFiles/8Puzzle.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/8Puzzle.dir/main.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/8Puzzle.dir/main.cpp.o -c /home/petko/workspace/FMI-Semester-6/8Puzzle/main.cpp

CMakeFiles/8Puzzle.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/8Puzzle.dir/main.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/8Puzzle/main.cpp > CMakeFiles/8Puzzle.dir/main.cpp.i

CMakeFiles/8Puzzle.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/8Puzzle.dir/main.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/8Puzzle/main.cpp -o CMakeFiles/8Puzzle.dir/main.cpp.s

CMakeFiles/8Puzzle.dir/Source/State.cpp.o: CMakeFiles/8Puzzle.dir/flags.make
CMakeFiles/8Puzzle.dir/Source/State.cpp.o: ../Source/State.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/8Puzzle.dir/Source/State.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/8Puzzle.dir/Source/State.cpp.o -c /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/State.cpp

CMakeFiles/8Puzzle.dir/Source/State.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/8Puzzle.dir/Source/State.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/State.cpp > CMakeFiles/8Puzzle.dir/Source/State.cpp.i

CMakeFiles/8Puzzle.dir/Source/State.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/8Puzzle.dir/Source/State.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/State.cpp -o CMakeFiles/8Puzzle.dir/Source/State.cpp.s

CMakeFiles/8Puzzle.dir/Source/Node.cpp.o: CMakeFiles/8Puzzle.dir/flags.make
CMakeFiles/8Puzzle.dir/Source/Node.cpp.o: ../Source/Node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/8Puzzle.dir/Source/Node.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/8Puzzle.dir/Source/Node.cpp.o -c /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/Node.cpp

CMakeFiles/8Puzzle.dir/Source/Node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/8Puzzle.dir/Source/Node.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/Node.cpp > CMakeFiles/8Puzzle.dir/Source/Node.cpp.i

CMakeFiles/8Puzzle.dir/Source/Node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/8Puzzle.dir/Source/Node.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/Node.cpp -o CMakeFiles/8Puzzle.dir/Source/Node.cpp.s

CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.o: CMakeFiles/8Puzzle.dir/flags.make
CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.o: ../Source/CompareFunctorForBestFirst.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.o -c /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/CompareFunctorForBestFirst.cpp

CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/CompareFunctorForBestFirst.cpp > CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.i

CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/CompareFunctorForBestFirst.cpp -o CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.s

CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.o: CMakeFiles/8Puzzle.dir/flags.make
CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.o: ../Source/CompareFunctorForAStar.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.o -c /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/CompareFunctorForAStar.cpp

CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/CompareFunctorForAStar.cpp > CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.i

CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/8Puzzle/Source/CompareFunctorForAStar.cpp -o CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.s

CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.o: CMakeFiles/8Puzzle.dir/flags.make
CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.o: ../Headers/Solver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.o"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.o -c /home/petko/workspace/FMI-Semester-6/8Puzzle/Headers/Solver.cpp

CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/8Puzzle/Headers/Solver.cpp > CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.i

CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/8Puzzle/Headers/Solver.cpp -o CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.s

# Object files for target 8Puzzle
8Puzzle_OBJECTS = \
"CMakeFiles/8Puzzle.dir/main.cpp.o" \
"CMakeFiles/8Puzzle.dir/Source/State.cpp.o" \
"CMakeFiles/8Puzzle.dir/Source/Node.cpp.o" \
"CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.o" \
"CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.o" \
"CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.o"

# External object files for target 8Puzzle
8Puzzle_EXTERNAL_OBJECTS =

8Puzzle: CMakeFiles/8Puzzle.dir/main.cpp.o
8Puzzle: CMakeFiles/8Puzzle.dir/Source/State.cpp.o
8Puzzle: CMakeFiles/8Puzzle.dir/Source/Node.cpp.o
8Puzzle: CMakeFiles/8Puzzle.dir/Source/CompareFunctorForBestFirst.cpp.o
8Puzzle: CMakeFiles/8Puzzle.dir/Source/CompareFunctorForAStar.cpp.o
8Puzzle: CMakeFiles/8Puzzle.dir/Headers/Solver.cpp.o
8Puzzle: CMakeFiles/8Puzzle.dir/build.make
8Puzzle: CMakeFiles/8Puzzle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable 8Puzzle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/8Puzzle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/8Puzzle.dir/build: 8Puzzle

.PHONY : CMakeFiles/8Puzzle.dir/build

CMakeFiles/8Puzzle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/8Puzzle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/8Puzzle.dir/clean

CMakeFiles/8Puzzle.dir/depend:
	cd /home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/petko/workspace/FMI-Semester-6/8Puzzle /home/petko/workspace/FMI-Semester-6/8Puzzle /home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug /home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug /home/petko/workspace/FMI-Semester-6/8Puzzle/cmake-build-debug/CMakeFiles/8Puzzle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/8Puzzle.dir/depend

