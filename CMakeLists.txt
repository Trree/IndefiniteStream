cmake_minimum_required(VERSION 3.3)
project (IndefiniteStream)
SET(CMAKE_C_COMPILER "g++") 
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#"${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
#"${PROJECT_BINARY_DIR}/share/tcp_server.h"
#
#)
option(Indefinite_ENABLE_TESTING "Enable testing of the library." ON)


# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
ADD_DEFINITIONS(-std=c++11 -g3 -W -Wall -pedantic -D_GNU_SOURCE)

# add the executable
add_executable(${PROJECT_NAME} main.cc)

if (Indefinite_ENABLE_TESTING)
  enable_testing()
  add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
  add_subdirectory(test)
endif()
