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
CMAKE_COMMAND = /app/extra/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /app/extra/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HeapSor.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HeapSor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HeapSor.dir/flags.make

CMakeFiles/HeapSor.dir/main.cpp.o: CMakeFiles/HeapSor.dir/flags.make
CMakeFiles/HeapSor.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HeapSor.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HeapSor.dir/main.cpp.o -c /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor/main.cpp

CMakeFiles/HeapSor.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HeapSor.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor/main.cpp > CMakeFiles/HeapSor.dir/main.cpp.i

CMakeFiles/HeapSor.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HeapSor.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor/main.cpp -o CMakeFiles/HeapSor.dir/main.cpp.s

# Object files for target HeapSor
HeapSor_OBJECTS = \
"CMakeFiles/HeapSor.dir/main.cpp.o"

# External object files for target HeapSor
HeapSor_EXTERNAL_OBJECTS =

HeapSor: CMakeFiles/HeapSor.dir/main.cpp.o
HeapSor: CMakeFiles/HeapSor.dir/build.make
HeapSor: CMakeFiles/HeapSor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HeapSor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HeapSor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HeapSor.dir/build: HeapSor

.PHONY : CMakeFiles/HeapSor.dir/build

CMakeFiles/HeapSor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HeapSor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HeapSor.dir/clean

CMakeFiles/HeapSor.dir/depend:
	cd /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor/cmake-build-debug /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor/cmake-build-debug /home/petko/workspace/FMI-Semester-6/Datastructures/HeapSor/cmake-build-debug/CMakeFiles/HeapSor.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HeapSor.dir/depend

