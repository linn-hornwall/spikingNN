# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Linn/neuro-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Linn/neuro-1/build

# Include any dependencies generated for this target.
include CMakeFiles/NeuronSimulation.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NeuronSimulation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NeuronSimulation.dir/flags.make

CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o: CMakeFiles/NeuronSimulation.dir/flags.make
CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o: ../src/Neuron.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Linn/neuro-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o -c /Users/Linn/neuro-1/src/Neuron.cpp

CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Linn/neuro-1/src/Neuron.cpp > CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.i

CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Linn/neuro-1/src/Neuron.cpp -o CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.s

CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o.requires:

.PHONY : CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o.requires

CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o.provides: CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o.requires
	$(MAKE) -f CMakeFiles/NeuronSimulation.dir/build.make CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o.provides.build
.PHONY : CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o.provides

CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o.provides.build: CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o


CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o: CMakeFiles/NeuronSimulation.dir/flags.make
CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o: ../src/Cortex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Linn/neuro-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o -c /Users/Linn/neuro-1/src/Cortex.cpp

CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Linn/neuro-1/src/Cortex.cpp > CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.i

CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Linn/neuro-1/src/Cortex.cpp -o CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.s

CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o.requires:

.PHONY : CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o.requires

CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o.provides: CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o.requires
	$(MAKE) -f CMakeFiles/NeuronSimulation.dir/build.make CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o.provides.build
.PHONY : CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o.provides

CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o.provides.build: CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o


CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o: CMakeFiles/NeuronSimulation.dir/flags.make
CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o: ../src/CortexInitializer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Linn/neuro-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o -c /Users/Linn/neuro-1/src/CortexInitializer.cpp

CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Linn/neuro-1/src/CortexInitializer.cpp > CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.i

CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Linn/neuro-1/src/CortexInitializer.cpp -o CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.s

CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o.requires:

.PHONY : CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o.requires

CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o.provides: CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o.requires
	$(MAKE) -f CMakeFiles/NeuronSimulation.dir/build.make CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o.provides.build
.PHONY : CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o.provides

CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o.provides.build: CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o


CMakeFiles/NeuronSimulation.dir/src/main.cpp.o: CMakeFiles/NeuronSimulation.dir/flags.make
CMakeFiles/NeuronSimulation.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Linn/neuro-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/NeuronSimulation.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NeuronSimulation.dir/src/main.cpp.o -c /Users/Linn/neuro-1/src/main.cpp

CMakeFiles/NeuronSimulation.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeuronSimulation.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Linn/neuro-1/src/main.cpp > CMakeFiles/NeuronSimulation.dir/src/main.cpp.i

CMakeFiles/NeuronSimulation.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeuronSimulation.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Linn/neuro-1/src/main.cpp -o CMakeFiles/NeuronSimulation.dir/src/main.cpp.s

CMakeFiles/NeuronSimulation.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/NeuronSimulation.dir/src/main.cpp.o.requires

CMakeFiles/NeuronSimulation.dir/src/main.cpp.o.provides: CMakeFiles/NeuronSimulation.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/NeuronSimulation.dir/build.make CMakeFiles/NeuronSimulation.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/NeuronSimulation.dir/src/main.cpp.o.provides

CMakeFiles/NeuronSimulation.dir/src/main.cpp.o.provides.build: CMakeFiles/NeuronSimulation.dir/src/main.cpp.o


# Object files for target NeuronSimulation
NeuronSimulation_OBJECTS = \
"CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o" \
"CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o" \
"CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o" \
"CMakeFiles/NeuronSimulation.dir/src/main.cpp.o"

# External object files for target NeuronSimulation
NeuronSimulation_EXTERNAL_OBJECTS =

NeuronSimulation: CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o
NeuronSimulation: CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o
NeuronSimulation: CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o
NeuronSimulation: CMakeFiles/NeuronSimulation.dir/src/main.cpp.o
NeuronSimulation: CMakeFiles/NeuronSimulation.dir/build.make
NeuronSimulation: CMakeFiles/NeuronSimulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Linn/neuro-1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable NeuronSimulation"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NeuronSimulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NeuronSimulation.dir/build: NeuronSimulation

.PHONY : CMakeFiles/NeuronSimulation.dir/build

CMakeFiles/NeuronSimulation.dir/requires: CMakeFiles/NeuronSimulation.dir/src/Neuron.cpp.o.requires
CMakeFiles/NeuronSimulation.dir/requires: CMakeFiles/NeuronSimulation.dir/src/Cortex.cpp.o.requires
CMakeFiles/NeuronSimulation.dir/requires: CMakeFiles/NeuronSimulation.dir/src/CortexInitializer.cpp.o.requires
CMakeFiles/NeuronSimulation.dir/requires: CMakeFiles/NeuronSimulation.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/NeuronSimulation.dir/requires

CMakeFiles/NeuronSimulation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NeuronSimulation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NeuronSimulation.dir/clean

CMakeFiles/NeuronSimulation.dir/depend:
	cd /Users/Linn/neuro-1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Linn/neuro-1 /Users/Linn/neuro-1 /Users/Linn/neuro-1/build /Users/Linn/neuro-1/build /Users/Linn/neuro-1/build/CMakeFiles/NeuronSimulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NeuronSimulation.dir/depend

