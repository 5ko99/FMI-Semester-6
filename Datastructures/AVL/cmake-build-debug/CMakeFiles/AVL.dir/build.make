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
CMAKE_SOURCE_DIR = /home/petko/workspace/FMI-Semester-6/Datastructures/AVL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/petko/workspace/FMI-Semester-6/Datastructures/AVL/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AVL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AVL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AVL.dir/flags.make

CMakeFiles/AVL.dir/main.cpp.o: CMakeFiles/AVL.dir/flags.make
CMakeFiles/AVL.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/petko/workspace/FMI-Semester-6/Datastructures/AVL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AVL.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AVL.dir/main.cpp.o -c /home/petko/workspace/FMI-Semester-6/Datastructures/AVL/main.cpp

CMakeFiles/AVL.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AVL.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/petko/workspace/FMI-Semester-6/Datastructures/AVL/main.cpp > CMakeFiles/AVL.dir/main.cpp.i

CMakeFiles/AVL.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AVL.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/petko/workspace/FMI-Semester-6/Datastructures/AVL/main.cpp -o CMakeFiles/AVL.dir/main.cpp.s

# Object files for target AVL
AVL_OBJECTS = \
"CMakeFiles/AVL.dir/main.cpp.o"

# External object files for target AVL
AVL_EXTERNAL_OBJECTS =

AVL: CMakeFiles/AVL.dir/main.cpp.o
AVL: CMakeFiles/AVL.dir/build.make
AVL: CMakeFiles/AVL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/petko/workspace/FMI-Semester-6/Datastructures/AVL/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AVL"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AVL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AVL.dir/build: AVL

.PHONY : CMakeFiles/AVL.dir/build

CMakeFiles/AVL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AVL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AVL.dir/clean

CMakeFiles/AVL.dir/depend:
	cd /home/petko/workspace/FMI-Semester-6/Datastructures/AVL/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/petko/workspace/FMI-Semester-6/Datastructures/AVL /home/petko/workspace/FMI-Semester-6/Datastructures/AVL /home/petko/workspace/FMI-Semester-6/Datastructures/AVL/cmake-build-debug /home/petko/workspace/FMI-Semester-6/Datastructures/AVL/cmake-build-debug /home/petko/workspace/FMI-Semester-6/Datastructures/AVL/cmake-build-debug/CMakeFiles/AVL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AVL.dir/depend

