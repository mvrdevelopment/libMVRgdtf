cmake_minimum_required(VERSION 3.10)

if (WIN32)
set(CMAKE_GENERATOR_PLATFORM x64)
endif(WIN32)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

# create the project
project(MvrGdtf)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PythonInterp REQUIRED)

# run python script for extracting and generating xerces
execute_process(COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/build_xerces.py
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE PY_OUTPUT)




# setup the platform macros
if (WIN32)
    set(EXTERN_INCLUDE ${PROJECT_SOURCE_DIR}/shared/xerces/build/libs/include)
else()
    set(EXTERN_INCLUDE ${PROJECT_SOURCE_DIR}/shared/include)
endif(WIN32)



include_directories(${PROJECT_SOURCE_DIR}/src
                    ${EXTERN_INCLUDE})

# default values
# those can be removed probably
set(SRCDIR ${PROJECT_SOURCE_DIR}/src)



# Add libary
# source files
file(GLOB_RECURSE libSourceFiles ${SRCDIR}/*.cpp)

add_library(VectorworksMvrGdtf STATIC ${libSourceFiles})

# setup the platform macros
if (WIN32)
    target_compile_definitions(VectorworksMvrGdtf PUBLIC GS_WIN)
    target_compile_definitions(VectorworksMvrGdtf PUBLIC _WINDOWS)
elseif(UNIX)
    if (APPLE)
        target_compile_definitions(VectorworksMvrGdtf PUBLIC GS_MAC)
    else()
        target_compile_definitions(VectorworksMvrGdtf PUBLIC GS_LIN)
        target_compile_definitions(VectorworksMvrGdtf PUBLIC _LINUX)
        #add_compile_definitions(GS_LIN)        
    endif(APPLE)
endif(WIN32)


# add the executable
# add_executable(libMvrGdtfUnitTest )