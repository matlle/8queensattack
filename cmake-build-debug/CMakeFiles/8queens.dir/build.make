# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /home/matlle/Files/IDEs/clion-2019.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/matlle/Files/IDEs/clion-2019.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/matlle/Projects/c++/modeling_simulation/8queens

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matlle/Projects/c++/modeling_simulation/8queens/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/8queens.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/8queens.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/8queens.dir/flags.make

CMakeFiles/8queens.dir/main.cpp.o: CMakeFiles/8queens.dir/flags.make
CMakeFiles/8queens.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matlle/Projects/c++/modeling_simulation/8queens/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/8queens.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/8queens.dir/main.cpp.o -c /home/matlle/Projects/c++/modeling_simulation/8queens/main.cpp

CMakeFiles/8queens.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/8queens.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matlle/Projects/c++/modeling_simulation/8queens/main.cpp > CMakeFiles/8queens.dir/main.cpp.i

CMakeFiles/8queens.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/8queens.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matlle/Projects/c++/modeling_simulation/8queens/main.cpp -o CMakeFiles/8queens.dir/main.cpp.s

# Object files for target 8queens
8queens_OBJECTS = \
"CMakeFiles/8queens.dir/main.cpp.o"

# External object files for target 8queens
8queens_EXTERNAL_OBJECTS =

8queens: CMakeFiles/8queens.dir/main.cpp.o
8queens: CMakeFiles/8queens.dir/build.make
8queens: CMakeFiles/8queens.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matlle/Projects/c++/modeling_simulation/8queens/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 8queens"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/8queens.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/8queens.dir/build: 8queens

.PHONY : CMakeFiles/8queens.dir/build

CMakeFiles/8queens.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/8queens.dir/cmake_clean.cmake
.PHONY : CMakeFiles/8queens.dir/clean

CMakeFiles/8queens.dir/depend:
	cd /home/matlle/Projects/c++/modeling_simulation/8queens/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matlle/Projects/c++/modeling_simulation/8queens /home/matlle/Projects/c++/modeling_simulation/8queens /home/matlle/Projects/c++/modeling_simulation/8queens/cmake-build-debug /home/matlle/Projects/c++/modeling_simulation/8queens/cmake-build-debug /home/matlle/Projects/c++/modeling_simulation/8queens/cmake-build-debug/CMakeFiles/8queens.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/8queens.dir/depend

