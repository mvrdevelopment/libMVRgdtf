cmake_minimum_required(VERSION 3.10)

# create the project
project(MvrGdtf)

include_directories(${PROJECT_SOURCE_DIR}/src)

# setup the platform macros
if (WIN32)
    add_definitions(GS_WIN)
elseif(UNIX)
    if (NOT APPLE)
        add_definitions(GS_LIN)        
    endif(NOT APPLE)
endif(WIN32)

# default values
set(SRCDIR ${PROJECT_SOURCE_DIR}/src)
set(SRCDIR_IMPL ${PROJECT_SOURCE_DIR}/src/Implementation)
set(SRCDIR_S256 ${PROJECT_SOURCE_DIR}/src/sha256)
set(SRCDIR_WRAP ${PROJECT_SOURCE_DIR}/src/Wrapper)
set(SRCDIR_XMLL ${PROJECT_SOURCE_DIR}/src/XMLLib)

set(SRCDIR_UNIT ${PROJECT_SOURCE_DIR}/unittest)
set(OBJDIR ${PROJECT_SOURCE_DIR}/obj)
set(BINDIR ${PROJECT_SOURCE_DIR}/x64/Release)
set(LIBDIR_PRE ${PROJECT_SOURCE_DIR}/libs)
set(LIBDIR_POST ${PROJECT_SOURCE_DIR}/release)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# Add libary
# source files
file(GLOB_RECURSE libSourceFiles ${SRCDIR}/*.cpp)

add_library(libMvrGdtf ${libSourceFiles})



# add the executable
# add_executable(libMvrGdtfUnitTest )