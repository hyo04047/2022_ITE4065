# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.24.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.24.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hataesung/Desktop/3-2/CP/project3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hataesung/Desktop/3-2/CP/project3/debug

# Include any dependencies generated for this target.
include bwtree/CMakeFiles/bwtree.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include bwtree/CMakeFiles/bwtree.dir/compiler_depend.make

# Include the progress variables for this target.
include bwtree/CMakeFiles/bwtree.dir/progress.make

# Include the compile flags for this target's objects.
include bwtree/CMakeFiles/bwtree.dir/flags.make

bwtree/CMakeFiles/bwtree.dir/src/bwtree.cc.o: bwtree/CMakeFiles/bwtree.dir/flags.make
bwtree/CMakeFiles/bwtree.dir/src/bwtree.cc.o: /Users/hataesung/Desktop/3-2/CP/project3/bwtree/src/bwtree.cc
bwtree/CMakeFiles/bwtree.dir/src/bwtree.cc.o: bwtree/CMakeFiles/bwtree.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hataesung/Desktop/3-2/CP/project3/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bwtree/CMakeFiles/bwtree.dir/src/bwtree.cc.o"
	cd /Users/hataesung/Desktop/3-2/CP/project3/debug/bwtree && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT bwtree/CMakeFiles/bwtree.dir/src/bwtree.cc.o -MF CMakeFiles/bwtree.dir/src/bwtree.cc.o.d -o CMakeFiles/bwtree.dir/src/bwtree.cc.o -c /Users/hataesung/Desktop/3-2/CP/project3/bwtree/src/bwtree.cc

bwtree/CMakeFiles/bwtree.dir/src/bwtree.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bwtree.dir/src/bwtree.cc.i"
	cd /Users/hataesung/Desktop/3-2/CP/project3/debug/bwtree && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hataesung/Desktop/3-2/CP/project3/bwtree/src/bwtree.cc > CMakeFiles/bwtree.dir/src/bwtree.cc.i

bwtree/CMakeFiles/bwtree.dir/src/bwtree.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bwtree.dir/src/bwtree.cc.s"
	cd /Users/hataesung/Desktop/3-2/CP/project3/debug/bwtree && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hataesung/Desktop/3-2/CP/project3/bwtree/src/bwtree.cc -o CMakeFiles/bwtree.dir/src/bwtree.cc.s

# Object files for target bwtree
bwtree_OBJECTS = \
"CMakeFiles/bwtree.dir/src/bwtree.cc.o"

# External object files for target bwtree
bwtree_EXTERNAL_OBJECTS =

lib/libbwtree.a: bwtree/CMakeFiles/bwtree.dir/src/bwtree.cc.o
lib/libbwtree.a: bwtree/CMakeFiles/bwtree.dir/build.make
lib/libbwtree.a: bwtree/CMakeFiles/bwtree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hataesung/Desktop/3-2/CP/project3/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../lib/libbwtree.a"
	cd /Users/hataesung/Desktop/3-2/CP/project3/debug/bwtree && $(CMAKE_COMMAND) -P CMakeFiles/bwtree.dir/cmake_clean_target.cmake
	cd /Users/hataesung/Desktop/3-2/CP/project3/debug/bwtree && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bwtree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bwtree/CMakeFiles/bwtree.dir/build: lib/libbwtree.a
.PHONY : bwtree/CMakeFiles/bwtree.dir/build

bwtree/CMakeFiles/bwtree.dir/clean:
	cd /Users/hataesung/Desktop/3-2/CP/project3/debug/bwtree && $(CMAKE_COMMAND) -P CMakeFiles/bwtree.dir/cmake_clean.cmake
.PHONY : bwtree/CMakeFiles/bwtree.dir/clean

bwtree/CMakeFiles/bwtree.dir/depend:
	cd /Users/hataesung/Desktop/3-2/CP/project3/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hataesung/Desktop/3-2/CP/project3 /Users/hataesung/Desktop/3-2/CP/project3/bwtree /Users/hataesung/Desktop/3-2/CP/project3/debug /Users/hataesung/Desktop/3-2/CP/project3/debug/bwtree /Users/hataesung/Desktop/3-2/CP/project3/debug/bwtree/CMakeFiles/bwtree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bwtree/CMakeFiles/bwtree.dir/depend

