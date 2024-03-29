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
include CMakeFiles/lanefollower.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lanefollower.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lanefollower.dir/flags.make

CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o: CMakeFiles/lanefollower.dir/flags.make
CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o: ../apps/lanefollower.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o -c /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/apps/lanefollower.cpp

CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/apps/lanefollower.cpp > CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.i

CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/apps/lanefollower.cpp -o CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.s

CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o.requires:
.PHONY : CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o.requires

CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o.provides: CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o.requires
	$(MAKE) -f CMakeFiles/lanefollower.dir/build.make CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o.provides.build
.PHONY : CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o.provides

CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o.provides.build: CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o

# Object files for target lanefollower
lanefollower_OBJECTS = \
"CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o"

# External object files for target lanefollower
lanefollower_EXTERNAL_OBJECTS =

lanefollower: CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o
lanefollower: CMakeFiles/lanefollower.dir/build.make
lanefollower: liblanefollowerlib-static.a
lanefollower: /usr/lib/libopendavinci.so
lanefollower: /usr/lib/x86_64-linux-gnu/librt.a
lanefollower: /usr/lib/libautomotivedata.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_core.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_flann.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_ml.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so
lanefollower: /usr/lib/x86_64-linux-gnu/libopencv_video.so
lanefollower: CMakeFiles/lanefollower.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable lanefollower"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lanefollower.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lanefollower.dir/build: lanefollower
.PHONY : CMakeFiles/lanefollower.dir/build

CMakeFiles/lanefollower.dir/requires: CMakeFiles/lanefollower.dir/apps/lanefollower.cpp.o.requires
.PHONY : CMakeFiles/lanefollower.dir/requires

CMakeFiles/lanefollower.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lanefollower.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lanefollower.dir/clean

CMakeFiles/lanefollower.dir/depend:
	cd /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build /home/rachele/OpenDaVINCI/automotive/miniature/lanefollower/build/CMakeFiles/lanefollower.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lanefollower.dir/depend

