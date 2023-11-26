cmake_minimum_required(VERSION 3.22)

project(glslbuilder VERSION 0.1.0)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,Release>:EditAndContinue>,$<$<CONFIG:Debug,Release>:ProgramDatabase>>")
endif()

option(BUILD_CLI "Build the Command Line Interface" OFF)
option(BUILD_TESTS "Build the tests" OFF)

add_subdirectory(glslbuilder)

if(BUILD_CLI)
	add_subdirectory(glslbuilder_exec)
endif()

if(BUILD_TESTS)
	add_subdirectory(glslbuilder_tests)
endif()