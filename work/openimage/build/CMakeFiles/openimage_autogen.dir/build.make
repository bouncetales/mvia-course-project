# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zk/Desktop/openimage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zk/Desktop/openimage/build

# Utility rule file for openimage_autogen.

# Include the progress variables for this target.
include CMakeFiles/openimage_autogen.dir/progress.make

CMakeFiles/openimage_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/zk/Desktop/openimage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC, UIC and RCC for target openimage"
	/usr/bin/cmake -E cmake_autogen /home/zk/Desktop/openimage/build/CMakeFiles/openimage_autogen.dir ""

openimage_autogen: CMakeFiles/openimage_autogen
openimage_autogen: CMakeFiles/openimage_autogen.dir/build.make

.PHONY : openimage_autogen

# Rule to build all files generated by this target.
CMakeFiles/openimage_autogen.dir/build: openimage_autogen

.PHONY : CMakeFiles/openimage_autogen.dir/build

CMakeFiles/openimage_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/openimage_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/openimage_autogen.dir/clean

CMakeFiles/openimage_autogen.dir/depend:
	cd /home/zk/Desktop/openimage/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zk/Desktop/openimage /home/zk/Desktop/openimage /home/zk/Desktop/openimage/build /home/zk/Desktop/openimage/build /home/zk/Desktop/openimage/build/CMakeFiles/openimage_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/openimage_autogen.dir/depend

