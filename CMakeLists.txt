#cmake version
cmake_minimum_required (VERSION 2.6)

#project name
project (neuro_1)

#build tests too
option(test "Build tests." ON)

#compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I ../lib/include -std=c++11 -O3 -W -Wall --pedantic")

#the executable of the project
add_executable (
	NeuronSimulation
	src/Neuron.cpp
	src/Cortex.cpp
	src/CortexInitializer.cpp
	src/main.cpp
)
target_link_libraries(NeuronSimulation m)

#doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT “Generating API Documentation with Doxygen” VERBATIM)
endif(DOXYGEN_FOUND)

#testing
if(test)
	enable_testing()
	find_package(GTest)
	include_directories(${GTEST_INCLUDE_DIRS})

  	add_definitions(-DTEST)
  
	add_executable(NeuronSimulation_test test/NeuronSimulationTest.cpp src/Cortex.cpp src/Neuron.cpp)
	target_link_libraries(NeuronSimulation_test ${GTEST_BOTH_LIBRARIES} pthread)
	add_test(neuro_1 NeuronSimulation_test)

endif(test)


	
