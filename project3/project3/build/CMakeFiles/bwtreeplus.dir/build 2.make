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
CMAKE_BINARY_DIR = /Users/hataesung/Desktop/3-2/CP/project3/build

# Include any dependencies generated for this target.
include CMakeFiles/bwtreeplus.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bwtreeplus.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bwtreeplus.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bwtreeplus.dir/flags.make

CMakeFiles/bwtreeplus.dir/main.cc.o: CMakeFiles/bwtreeplus.dir/flags.make
CMakeFiles/bwtreeplus.dir/main.cc.o: /Users/hataesung/Desktop/3-2/CP/project3/main.cc
CMakeFiles/bwtreeplus.dir/main.cc.o: CMakeFiles/bwtreeplus.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hataesung/Desktop/3-2/CP/project3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bwtreeplus.dir/main.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bwtreeplus.dir/main.cc.o -MF CMakeFiles/bwtreeplus.dir/main.cc.o.d -o CMakeFiles/bwtreeplus.dir/main.cc.o -c /Users/hataesung/Desktop/3-2/CP/project3/main.cc

CMakeFiles/bwtreeplus.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bwtreeplus.dir/main.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hataesung/Desktop/3-2/CP/project3/main.cc > CMakeFiles/bwtreeplus.dir/main.cc.i

CMakeFiles/bwtreeplus.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bwtreeplus.dir/main.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hataesung/Desktop/3-2/CP/project3/main.cc -o CMakeFiles/bwtreeplus.dir/main.cc.s

# Object files for target bwtreeplus
bwtreeplus_OBJECTS = \
"CMakeFiles/bwtreeplus.dir/main.cc.o"

# External object files for target bwtreeplus
bwtreeplus_EXTERNAL_OBJECTS =

bin/bwtreeplus: CMakeFiles/bwtreeplus.dir/main.cc.o
bin/bwtreeplus: CMakeFiles/bwtreeplus.dir/build.make
bin/bwtreeplus: lib/libbwtree.a
bin/bwtreeplus: CMakeFiles/bwtreeplus.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hataesung/Desktop/3-2/CP/project3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/bwtreeplus"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bwtreeplus.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bwtreeplus.dir/build: bin/bwtreeplus
.PHONY : CMakeFiles/bwtreeplus.dir/build

CMakeFiles/bwtreeplus.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bwtreeplus.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bwtreeplus.dir/clean

CMakeFiles/bwtreeplus.dir/depend:
	cd /Users/hataesung/Desktop/3-2/CP/project3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hataesung/Desktop/3-2/CP/project3 /Users/hataesung/Desktop/3-2/CP/project3 /Users/hataesung/Desktop/3-2/CP/project3/build /Users/hataesung/Desktop/3-2/CP/project3/build /Users/hataesung/Desktop/3-2/CP/project3/build/CMakeFiles/bwtreeplus.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bwtreeplus.dir/depend

