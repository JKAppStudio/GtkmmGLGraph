# GtkmmGLGraph CMake configuration
cmake_minimum_required(VERSION 3.19)
project(GtkmmGLGraph C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(cmake/finddeps.cmake)
include(cmake/options.cmake)
include(cmake/lib.cmake)
include(cmake/examples.cmake)