# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007

# Include any dependencies generated for this target.
include CMakeFiles/main_restoration.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main_restoration.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main_restoration.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main_restoration.dir/flags.make

CMakeFiles/main_restoration.dir/src/main_restoration.cpp.o: CMakeFiles/main_restoration.dir/flags.make
CMakeFiles/main_restoration.dir/src/main_restoration.cpp.o: src/main_restoration.cpp
CMakeFiles/main_restoration.dir/src/main_restoration.cpp.o: CMakeFiles/main_restoration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main_restoration.dir/src/main_restoration.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_restoration.dir/src/main_restoration.cpp.o -MF CMakeFiles/main_restoration.dir/src/main_restoration.cpp.o.d -o CMakeFiles/main_restoration.dir/src/main_restoration.cpp.o -c /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/main_restoration.cpp

CMakeFiles/main_restoration.dir/src/main_restoration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_restoration.dir/src/main_restoration.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/main_restoration.cpp > CMakeFiles/main_restoration.dir/src/main_restoration.cpp.i

CMakeFiles/main_restoration.dir/src/main_restoration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_restoration.dir/src/main_restoration.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/main_restoration.cpp -o CMakeFiles/main_restoration.dir/src/main_restoration.cpp.s

CMakeFiles/main_restoration.dir/src/dip.cpp.o: CMakeFiles/main_restoration.dir/flags.make
CMakeFiles/main_restoration.dir/src/dip.cpp.o: src/dip.cpp
CMakeFiles/main_restoration.dir/src/dip.cpp.o: CMakeFiles/main_restoration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main_restoration.dir/src/dip.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_restoration.dir/src/dip.cpp.o -MF CMakeFiles/main_restoration.dir/src/dip.cpp.o.d -o CMakeFiles/main_restoration.dir/src/dip.cpp.o -c /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/dip.cpp

CMakeFiles/main_restoration.dir/src/dip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_restoration.dir/src/dip.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/dip.cpp > CMakeFiles/main_restoration.dir/src/dip.cpp.i

CMakeFiles/main_restoration.dir/src/dip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_restoration.dir/src/dip.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/dip.cpp -o CMakeFiles/main_restoration.dir/src/dip.cpp.s

CMakeFiles/main_restoration.dir/src/bitmap.cpp.o: CMakeFiles/main_restoration.dir/flags.make
CMakeFiles/main_restoration.dir/src/bitmap.cpp.o: src/bitmap.cpp
CMakeFiles/main_restoration.dir/src/bitmap.cpp.o: CMakeFiles/main_restoration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main_restoration.dir/src/bitmap.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_restoration.dir/src/bitmap.cpp.o -MF CMakeFiles/main_restoration.dir/src/bitmap.cpp.o.d -o CMakeFiles/main_restoration.dir/src/bitmap.cpp.o -c /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/bitmap.cpp

CMakeFiles/main_restoration.dir/src/bitmap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_restoration.dir/src/bitmap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/bitmap.cpp > CMakeFiles/main_restoration.dir/src/bitmap.cpp.i

CMakeFiles/main_restoration.dir/src/bitmap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_restoration.dir/src/bitmap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/bitmap.cpp -o CMakeFiles/main_restoration.dir/src/bitmap.cpp.s

CMakeFiles/main_restoration.dir/src/define.cpp.o: CMakeFiles/main_restoration.dir/flags.make
CMakeFiles/main_restoration.dir/src/define.cpp.o: src/define.cpp
CMakeFiles/main_restoration.dir/src/define.cpp.o: CMakeFiles/main_restoration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main_restoration.dir/src/define.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_restoration.dir/src/define.cpp.o -MF CMakeFiles/main_restoration.dir/src/define.cpp.o.d -o CMakeFiles/main_restoration.dir/src/define.cpp.o -c /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/define.cpp

CMakeFiles/main_restoration.dir/src/define.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_restoration.dir/src/define.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/define.cpp > CMakeFiles/main_restoration.dir/src/define.cpp.i

CMakeFiles/main_restoration.dir/src/define.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_restoration.dir/src/define.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/define.cpp -o CMakeFiles/main_restoration.dir/src/define.cpp.s

CMakeFiles/main_restoration.dir/src/freq_helper.cpp.o: CMakeFiles/main_restoration.dir/flags.make
CMakeFiles/main_restoration.dir/src/freq_helper.cpp.o: src/freq_helper.cpp
CMakeFiles/main_restoration.dir/src/freq_helper.cpp.o: CMakeFiles/main_restoration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main_restoration.dir/src/freq_helper.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_restoration.dir/src/freq_helper.cpp.o -MF CMakeFiles/main_restoration.dir/src/freq_helper.cpp.o.d -o CMakeFiles/main_restoration.dir/src/freq_helper.cpp.o -c /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/freq_helper.cpp

CMakeFiles/main_restoration.dir/src/freq_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_restoration.dir/src/freq_helper.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/freq_helper.cpp > CMakeFiles/main_restoration.dir/src/freq_helper.cpp.i

CMakeFiles/main_restoration.dir/src/freq_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_restoration.dir/src/freq_helper.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/freq_helper.cpp -o CMakeFiles/main_restoration.dir/src/freq_helper.cpp.s

CMakeFiles/main_restoration.dir/src/argparse.cpp.o: CMakeFiles/main_restoration.dir/flags.make
CMakeFiles/main_restoration.dir/src/argparse.cpp.o: src/argparse.cpp
CMakeFiles/main_restoration.dir/src/argparse.cpp.o: CMakeFiles/main_restoration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main_restoration.dir/src/argparse.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_restoration.dir/src/argparse.cpp.o -MF CMakeFiles/main_restoration.dir/src/argparse.cpp.o.d -o CMakeFiles/main_restoration.dir/src/argparse.cpp.o -c /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/argparse.cpp

CMakeFiles/main_restoration.dir/src/argparse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_restoration.dir/src/argparse.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/argparse.cpp > CMakeFiles/main_restoration.dir/src/argparse.cpp.i

CMakeFiles/main_restoration.dir/src/argparse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_restoration.dir/src/argparse.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/src/argparse.cpp -o CMakeFiles/main_restoration.dir/src/argparse.cpp.s

# Object files for target main_restoration
main_restoration_OBJECTS = \
"CMakeFiles/main_restoration.dir/src/main_restoration.cpp.o" \
"CMakeFiles/main_restoration.dir/src/dip.cpp.o" \
"CMakeFiles/main_restoration.dir/src/bitmap.cpp.o" \
"CMakeFiles/main_restoration.dir/src/define.cpp.o" \
"CMakeFiles/main_restoration.dir/src/freq_helper.cpp.o" \
"CMakeFiles/main_restoration.dir/src/argparse.cpp.o"

# External object files for target main_restoration
main_restoration_EXTERNAL_OBJECTS =

main_restoration: CMakeFiles/main_restoration.dir/src/main_restoration.cpp.o
main_restoration: CMakeFiles/main_restoration.dir/src/dip.cpp.o
main_restoration: CMakeFiles/main_restoration.dir/src/bitmap.cpp.o
main_restoration: CMakeFiles/main_restoration.dir/src/define.cpp.o
main_restoration: CMakeFiles/main_restoration.dir/src/freq_helper.cpp.o
main_restoration: CMakeFiles/main_restoration.dir/src/argparse.cpp.o
main_restoration: CMakeFiles/main_restoration.dir/build.make
main_restoration: /usr/local/lib/libopencv_gapi.so.4.8.0
main_restoration: /usr/local/lib/libopencv_highgui.so.4.8.0
main_restoration: /usr/local/lib/libopencv_ml.so.4.8.0
main_restoration: /usr/local/lib/libopencv_objdetect.so.4.8.0
main_restoration: /usr/local/lib/libopencv_photo.so.4.8.0
main_restoration: /usr/local/lib/libopencv_stitching.so.4.8.0
main_restoration: /usr/local/lib/libopencv_video.so.4.8.0
main_restoration: /usr/local/lib/libopencv_videoio.so.4.8.0
main_restoration: /usr/local/lib/libopencv_imgcodecs.so.4.8.0
main_restoration: /usr/local/lib/libopencv_dnn.so.4.8.0
main_restoration: /usr/local/lib/libopencv_calib3d.so.4.8.0
main_restoration: /usr/local/lib/libopencv_features2d.so.4.8.0
main_restoration: /usr/local/lib/libopencv_flann.so.4.8.0
main_restoration: /usr/local/lib/libopencv_imgproc.so.4.8.0
main_restoration: /usr/local/lib/libopencv_core.so.4.8.0
main_restoration: CMakeFiles/main_restoration.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable main_restoration"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main_restoration.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main_restoration.dir/build: main_restoration
.PHONY : CMakeFiles/main_restoration.dir/build

CMakeFiles/main_restoration.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main_restoration.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main_restoration.dir/clean

CMakeFiles/main_restoration.dir/depend:
	cd /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007 /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007 /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007 /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007 /mnt/d/DIP/src/Digital-Image-Processing_2023/hw4_311833007/CMakeFiles/main_restoration.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main_restoration.dir/depend

