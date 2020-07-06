cmake_minimum_required(VERSION 3.10)

# create the project
project(MvrGdtf)

find_package(PythonInterp REQUIRED)

# run python script for extracting and generating xerces
execute_process(COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/gen_xerces.py
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE PY_OUTPUT)
message("Xerces build output: " ${PY_OUTPUT})

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/shared/include)




# setup the platform macros
if (WIN32)
    add_compile_definitions(GS_WIN)
elseif(UNIX)
    if (APPLE)
    add_compile_definitions(GS_MAC)
    else()
    add_compile_definitions(GS_LIN)        
    endif(APPLE)
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

add_library(VectorworksMvrGdtf STATIC ${libSourceFiles})


# add deps



## xerces
add_subdirectory(${PROJECT_SOURCE_DIR}/shared/xerces-c-3.2.2)



# add the executable
# add_executable(libMvrGdtfUnitTest )