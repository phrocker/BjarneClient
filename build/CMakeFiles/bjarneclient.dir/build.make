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
CMAKE_SOURCE_DIR = /home/marc/BjarneClient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marc/BjarneClient/build

# Include any dependencies generated for this target.
include CMakeFiles/bjarneclient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bjarneclient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bjarneclient.dir/flags.make

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o: CMakeFiles/bjarneclient.dir/flags.make
CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o: ../src/data/constructs/client/zookeeper/watch.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/marc/BjarneClient/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o -c /home/marc/BjarneClient/src/data/constructs/client/zookeeper/watch.cpp

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/marc/BjarneClient/src/data/constructs/client/zookeeper/watch.cpp > CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.i

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/marc/BjarneClient/src/data/constructs/client/zookeeper/watch.cpp -o CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.s

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o.requires:
.PHONY : CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o.requires

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o.provides: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o.requires
	$(MAKE) -f CMakeFiles/bjarneclient.dir/build.make CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o.provides.build
.PHONY : CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o.provides

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o.provides.build: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o: CMakeFiles/bjarneclient.dir/flags.make
CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o: ../src/data/constructs/client/zookeeper/zookeepers.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/marc/BjarneClient/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o -c /home/marc/BjarneClient/src/data/constructs/client/zookeeper/zookeepers.cpp

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/marc/BjarneClient/src/data/constructs/client/zookeeper/zookeepers.cpp > CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.i

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/marc/BjarneClient/src/data/constructs/client/zookeeper/zookeepers.cpp -o CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.s

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o.requires:
.PHONY : CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o.requires

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o.provides: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o.requires
	$(MAKE) -f CMakeFiles/bjarneclient.dir/build.make CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o.provides.build
.PHONY : CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o.provides

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o.provides.build: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o: CMakeFiles/bjarneclient.dir/flags.make
CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o: ../src/data/constructs/client/zookeeperinstance.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/marc/BjarneClient/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o -c /home/marc/BjarneClient/src/data/constructs/client/zookeeperinstance.cpp

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/marc/BjarneClient/src/data/constructs/client/zookeeperinstance.cpp > CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.i

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/marc/BjarneClient/src/data/constructs/client/zookeeperinstance.cpp -o CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.s

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o.requires:
.PHONY : CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o.requires

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o.provides: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o.requires
	$(MAKE) -f CMakeFiles/bjarneclient.dir/build.make CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o.provides.build
.PHONY : CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o.provides

CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o.provides.build: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o

CMakeFiles/bjarneclient.dir/main.o: CMakeFiles/bjarneclient.dir/flags.make
CMakeFiles/bjarneclient.dir/main.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/marc/BjarneClient/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/bjarneclient.dir/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bjarneclient.dir/main.o -c /home/marc/BjarneClient/main.cpp

CMakeFiles/bjarneclient.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bjarneclient.dir/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/marc/BjarneClient/main.cpp > CMakeFiles/bjarneclient.dir/main.i

CMakeFiles/bjarneclient.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bjarneclient.dir/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/marc/BjarneClient/main.cpp -o CMakeFiles/bjarneclient.dir/main.s

CMakeFiles/bjarneclient.dir/main.o.requires:
.PHONY : CMakeFiles/bjarneclient.dir/main.o.requires

CMakeFiles/bjarneclient.dir/main.o.provides: CMakeFiles/bjarneclient.dir/main.o.requires
	$(MAKE) -f CMakeFiles/bjarneclient.dir/build.make CMakeFiles/bjarneclient.dir/main.o.provides.build
.PHONY : CMakeFiles/bjarneclient.dir/main.o.provides

CMakeFiles/bjarneclient.dir/main.o.provides.build: CMakeFiles/bjarneclient.dir/main.o

# Object files for target bjarneclient
bjarneclient_OBJECTS = \
"CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o" \
"CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o" \
"CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o" \
"CMakeFiles/bjarneclient.dir/main.o"

# External object files for target bjarneclient
bjarneclient_EXTERNAL_OBJECTS =

bjarneclient: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o
bjarneclient: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o
bjarneclient: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o
bjarneclient: CMakeFiles/bjarneclient.dir/main.o
bjarneclient: CMakeFiles/bjarneclient.dir/build.make
bjarneclient: CMakeFiles/bjarneclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bjarneclient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bjarneclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bjarneclient.dir/build: bjarneclient
.PHONY : CMakeFiles/bjarneclient.dir/build

CMakeFiles/bjarneclient.dir/requires: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/watch.o.requires
CMakeFiles/bjarneclient.dir/requires: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeper/zookeepers.o.requires
CMakeFiles/bjarneclient.dir/requires: CMakeFiles/bjarneclient.dir/src/data/constructs/client/zookeeperinstance.o.requires
CMakeFiles/bjarneclient.dir/requires: CMakeFiles/bjarneclient.dir/main.o.requires
.PHONY : CMakeFiles/bjarneclient.dir/requires

CMakeFiles/bjarneclient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bjarneclient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bjarneclient.dir/clean

CMakeFiles/bjarneclient.dir/depend:
	cd /home/marc/BjarneClient/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marc/BjarneClient /home/marc/BjarneClient /home/marc/BjarneClient/build /home/marc/BjarneClient/build /home/marc/BjarneClient/build/CMakeFiles/bjarneclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bjarneclient.dir/depend

