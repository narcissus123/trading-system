# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hamidzargar/CLionProjects/tradingsystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug

# Include any dependencies generated for this target.
include yahoo-finance-master/CMakeFiles/example.dir/depend.make
# Include the progress variables for this target.
include yahoo-finance-master/CMakeFiles/example.dir/progress.make

# Include the compile flags for this target's objects.
include yahoo-finance-master/CMakeFiles/example.dir/flags.make

yahoo-finance-master/CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.o: yahoo-finance-master/CMakeFiles/example.dir/flags.make
yahoo-finance-master/CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.o: yahoo-finance-master/example_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object yahoo-finance-master/CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.o"
	cd /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.o -c /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master/example_autogen/mocs_compilation.cpp

yahoo-finance-master/CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.i"
	cd /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master/example_autogen/mocs_compilation.cpp > CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.i

yahoo-finance-master/CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.s"
	cd /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master/example_autogen/mocs_compilation.cpp -o CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.s

yahoo-finance-master/CMakeFiles/example.dir/src/example.cpp.o: yahoo-finance-master/CMakeFiles/example.dir/flags.make
yahoo-finance-master/CMakeFiles/example.dir/src/example.cpp.o: ../yahoo-finance-master/src/example.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object yahoo-finance-master/CMakeFiles/example.dir/src/example.cpp.o"
	cd /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example.dir/src/example.cpp.o -c /Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master/src/example.cpp

yahoo-finance-master/CMakeFiles/example.dir/src/example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example.dir/src/example.cpp.i"
	cd /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master/src/example.cpp > CMakeFiles/example.dir/src/example.cpp.i

yahoo-finance-master/CMakeFiles/example.dir/src/example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example.dir/src/example.cpp.s"
	cd /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master/src/example.cpp -o CMakeFiles/example.dir/src/example.cpp.s

# Object files for target example
example_OBJECTS = \
"CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/example.dir/src/example.cpp.o"

# External object files for target example
example_EXTERNAL_OBJECTS =

yahoo-finance-master/example: yahoo-finance-master/CMakeFiles/example.dir/example_autogen/mocs_compilation.cpp.o
yahoo-finance-master/example: yahoo-finance-master/CMakeFiles/example.dir/src/example.cpp.o
yahoo-finance-master/example: yahoo-finance-master/CMakeFiles/example.dir/build.make
yahoo-finance-master/example: yahoo-finance-master/libyahoo-finance.a
yahoo-finance-master/example: yahoo-finance-master/CMakeFiles/example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable example"
	cd /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
yahoo-finance-master/CMakeFiles/example.dir/build: yahoo-finance-master/example
.PHONY : yahoo-finance-master/CMakeFiles/example.dir/build

yahoo-finance-master/CMakeFiles/example.dir/clean:
	cd /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master && $(CMAKE_COMMAND) -P CMakeFiles/example.dir/cmake_clean.cmake
.PHONY : yahoo-finance-master/CMakeFiles/example.dir/clean

yahoo-finance-master/CMakeFiles/example.dir/depend:
	cd /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hamidzargar/CLionProjects/tradingsystem /Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master/CMakeFiles/example.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : yahoo-finance-master/CMakeFiles/example.dir/depend
