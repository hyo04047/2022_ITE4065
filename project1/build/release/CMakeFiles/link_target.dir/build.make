# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /root/CP/submission

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/CP/submission/build/release

# Utility rule file for link_target.

# Include the progress variables for this target.
include CMakeFiles/link_target.dir/progress.make

CMakeFiles/link_target:
	/usr/bin/cmake -E create_symlink /root/CP/submission/workloads /root/CP/submission/build/release/workloads

link_target: CMakeFiles/link_target
link_target: CMakeFiles/link_target.dir/build.make

.PHONY : link_target

# Rule to build all files generated by this target.
CMakeFiles/link_target.dir/build: link_target

.PHONY : CMakeFiles/link_target.dir/build

CMakeFiles/link_target.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/link_target.dir/cmake_clean.cmake
.PHONY : CMakeFiles/link_target.dir/clean

CMakeFiles/link_target.dir/depend:
	cd /root/CP/submission/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/CP/submission /root/CP/submission /root/CP/submission/build/release /root/CP/submission/build/release /root/CP/submission/build/release/CMakeFiles/link_target.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/link_target.dir/depend

