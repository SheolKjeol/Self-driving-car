# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build

# Include any dependencies generated for this target.
include CMakeFiles/lanefollowerlib-static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lanefollowerlib-static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lanefollowerlib-static.dir/flags.make

CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o: CMakeFiles/lanefollowerlib-static.dir/flags.make
CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o: ../src/LaneFollower.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o -c /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/src/LaneFollower.cpp

CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/src/LaneFollower.cpp > CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.i

CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/src/LaneFollower.cpp -o CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.s

CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o.requires:
.PHONY : CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o.requires

CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o.provides: CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o.requires
	$(MAKE) -f CMakeFiles/lanefollowerlib-static.dir/build.make CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o.provides.build
.PHONY : CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o.provides

CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o.provides.build: CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o

# Object files for target lanefollowerlib-static
lanefollowerlib__static_OBJECTS = \
"CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o"

# External object files for target lanefollowerlib-static
lanefollowerlib__static_EXTERNAL_OBJECTS =

liblanefollowerlib-static.a: CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o
liblanefollowerlib-static.a: CMakeFiles/lanefollowerlib-static.dir/build.make
liblanefollowerlib-static.a: CMakeFiles/lanefollowerlib-static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library liblanefollowerlib-static.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lanefollowerlib-static.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lanefollowerlib-static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lanefollowerlib-static.dir/build: liblanefollowerlib-static.a
.PHONY : CMakeFiles/lanefollowerlib-static.dir/build

CMakeFiles/lanefollowerlib-static.dir/requires: CMakeFiles/lanefollowerlib-static.dir/src/LaneFollower.cpp.o.requires
.PHONY : CMakeFiles/lanefollowerlib-static.dir/requires

CMakeFiles/lanefollowerlib-static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lanefollowerlib-static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lanefollowerlib-static.dir/clean

CMakeFiles/lanefollowerlib-static.dir/depend:
	cd /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build/CMakeFiles/lanefollowerlib-static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lanefollowerlib-static.dir/depend

