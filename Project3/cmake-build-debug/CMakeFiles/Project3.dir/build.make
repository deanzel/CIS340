# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/deanchoi/CLionProjects/CIS340/Project3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/deanchoi/CLionProjects/CIS340/Project3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Project3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project3.dir/flags.make

CMakeFiles/Project3.dir/main.c.o: CMakeFiles/Project3.dir/flags.make
CMakeFiles/Project3.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deanchoi/CLionProjects/CIS340/Project3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Project3.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project3.dir/main.c.o   -c /Users/deanchoi/CLionProjects/CIS340/Project3/main.c

CMakeFiles/Project3.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project3.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/deanchoi/CLionProjects/CIS340/Project3/main.c > CMakeFiles/Project3.dir/main.c.i

CMakeFiles/Project3.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project3.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/deanchoi/CLionProjects/CIS340/Project3/main.c -o CMakeFiles/Project3.dir/main.c.s

CMakeFiles/Project3.dir/main.c.o.requires:

.PHONY : CMakeFiles/Project3.dir/main.c.o.requires

CMakeFiles/Project3.dir/main.c.o.provides: CMakeFiles/Project3.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/Project3.dir/build.make CMakeFiles/Project3.dir/main.c.o.provides.build
.PHONY : CMakeFiles/Project3.dir/main.c.o.provides

CMakeFiles/Project3.dir/main.c.o.provides.build: CMakeFiles/Project3.dir/main.c.o


CMakeFiles/Project3.dir/shell.c.o: CMakeFiles/Project3.dir/flags.make
CMakeFiles/Project3.dir/shell.c.o: ../shell.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/deanchoi/CLionProjects/CIS340/Project3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Project3.dir/shell.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project3.dir/shell.c.o   -c /Users/deanchoi/CLionProjects/CIS340/Project3/shell.c

CMakeFiles/Project3.dir/shell.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project3.dir/shell.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/deanchoi/CLionProjects/CIS340/Project3/shell.c > CMakeFiles/Project3.dir/shell.c.i

CMakeFiles/Project3.dir/shell.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project3.dir/shell.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/deanchoi/CLionProjects/CIS340/Project3/shell.c -o CMakeFiles/Project3.dir/shell.c.s

CMakeFiles/Project3.dir/shell.c.o.requires:

.PHONY : CMakeFiles/Project3.dir/shell.c.o.requires

CMakeFiles/Project3.dir/shell.c.o.provides: CMakeFiles/Project3.dir/shell.c.o.requires
	$(MAKE) -f CMakeFiles/Project3.dir/build.make CMakeFiles/Project3.dir/shell.c.o.provides.build
.PHONY : CMakeFiles/Project3.dir/shell.c.o.provides

CMakeFiles/Project3.dir/shell.c.o.provides.build: CMakeFiles/Project3.dir/shell.c.o


# Object files for target Project3
Project3_OBJECTS = \
"CMakeFiles/Project3.dir/main.c.o" \
"CMakeFiles/Project3.dir/shell.c.o"

# External object files for target Project3
Project3_EXTERNAL_OBJECTS =

Project3: CMakeFiles/Project3.dir/main.c.o
Project3: CMakeFiles/Project3.dir/shell.c.o
Project3: CMakeFiles/Project3.dir/build.make
Project3: CMakeFiles/Project3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/deanchoi/CLionProjects/CIS340/Project3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Project3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project3.dir/build: Project3

.PHONY : CMakeFiles/Project3.dir/build

CMakeFiles/Project3.dir/requires: CMakeFiles/Project3.dir/main.c.o.requires
CMakeFiles/Project3.dir/requires: CMakeFiles/Project3.dir/shell.c.o.requires

.PHONY : CMakeFiles/Project3.dir/requires

CMakeFiles/Project3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project3.dir/clean

CMakeFiles/Project3.dir/depend:
	cd /Users/deanchoi/CLionProjects/CIS340/Project3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/deanchoi/CLionProjects/CIS340/Project3 /Users/deanchoi/CLionProjects/CIS340/Project3 /Users/deanchoi/CLionProjects/CIS340/Project3/cmake-build-debug /Users/deanchoi/CLionProjects/CIS340/Project3/cmake-build-debug /Users/deanchoi/CLionProjects/CIS340/Project3/cmake-build-debug/CMakeFiles/Project3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Project3.dir/depend

