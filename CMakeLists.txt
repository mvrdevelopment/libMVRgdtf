cmake_minimum_required(VERSION 3.9.4)

# pre setup for some vars
set(UNITTEST TRUE CACHE STRING "If enabled the tests wont be build!")
set(WIN_RELEASE_TYPE CACHE STRING "Set '-MD' or '-MT' for windows build")


set(PYTHON_ARGS "TETSASDLKAJSDLKAJSDLKJASDLKJASDLKJASD")
#################################################
# System setup
if (WIN32)
set(CMAKE_GENERATOR_PLATFORM x64)
set(PYTHON_ARGS "MD")
elseif(APPLE)
    if($ENV{OSX_VERSION})
    message("Setting osx version: " $ENV{OSX_VERSION})
        set(CMAKE_OSX_DEPLOYMENT_TARGET $ENV{OSX_VERSION})
    endif($ENV{OSX_VERSION})
endif(WIN32)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)


#################################################


#################################################
# create the project
project(MvrGdtf)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output dir
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/)



#################################################
# Building Xerces

if(WIN32)
endif(WIN32)


find_package(PythonInterp REQUIRED)
# run python script for extracting and generating xerces
execute_process(COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/build_xerces.py ${PYTHON_ARGS}
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE PY_OUTPUT)

#################################################


# setup the platform macros
if (WIN32)
    set(XERCES_INCLUDE ${PROJECT_SOURCE_DIR}/shared/xerces/build/libs/include)
    set(XERCES_LIB ${PROJECT_SOURCE_DIR}/libs/lib/xerces-c_3.lib)
else()
    set(XERCES_INCLUDE ${PROJECT_SOURCE_DIR}/shared/include)
    set(XERCES_LIB ${PROJECT_SOURCE_DIR}/libs/libxerces-c.a)
endif(WIN32)



include_directories(${PROJECT_SOURCE_DIR}/src
                    ${XERCES_INCLUDE})

# default values
# those can be removed probably
set(SRCDIR ${PROJECT_SOURCE_DIR}/src)
set(SRC_TESTDIR ${PROJECT_SOURCE_DIR}/unittest)






#################################################
# Add libVectorworksMvrGdtf lib
file(GLOB_RECURSE libSourceFiles ${SRCDIR}/*.cpp)
add_library(VectorworksMvrGdtf STATIC ${libSourceFiles})

target_link_libraries(VectorworksMvrGdtf ${XERCES_LIB})
#################################################


#################################################
############### add unit tests ##################
if (UNITTEST)

file(GLOB_RECURSE unitTestSourceFiles ${SRC_TESTDIR}/*.cpp)
add_executable(MvrGdtfUnitTest  ${unitTestSourceFiles})

add_definitions(-DGITPATH="${PROJECT_SOURCE_DIR}")
target_link_libraries(MvrGdtfUnitTest VectorworksMvrGdtf)
    
endif (UNITTEST)
#################################################



#################################################
# setup the platform macros
if (WIN32)
    set(PREPROCESSORS ${PREPROCESSORS} PUBLIC GS_WIN)
    set(PREPROCESSORS ${PREPROCESSORS} PUBLIC _WINDOWS)
    
    set(EXTRA_LIBS ${EXTRA_LIBS} rpcrt4)
    set(EXTRA_LIBS ${EXTRA_LIBS} shlwapi)
elseif(UNIX)
    if (APPLE)
        set(PREPROCESSORS ${PREPROCESSORS} PUBLIC GS_MAC)
        set(PREPROCESSORS ${PREPROCESSORS} PUBLIC __APPLE__)

        find_library( MAC_CORESERVICE CoreServices )
        find_library( MAC_COREFOUNDATION CoreFoundation )
        
        set(EXTRA_LIBS ${EXTRA_LIBS} ${MAC_CORESERVICE} ${MAC_COREFOUNDATION})
    else()
        set(PREPROCESSORS ${PREPROCESSORS} PUBLIC GS_LIN)
        set(PREPROCESSORS ${PREPROCESSORS} PUBLIC _LINUX)

        set(EXTRA_LIBS ${EXTRA_LIBS} uuid)
        #add_compile_definitions(GS_LIN)        
    endif(APPLE)

    set(EXTRA_LIBS ${EXTRA_LIBS} pthread)
endif(WIN32)
#################################################


#################################################
# Add the preprocessors
# Link extra libs
target_compile_definitions(VectorworksMvrGdtf ${PREPROCESSORS})
target_link_libraries(VectorworksMvrGdtf ${EXTRA_LIBS})

if(${UNITTEST})
target_compile_definitions(MvrGdtfUnitTest ${PREPROCESSORS})
target_link_libraries(MvrGdtfUnitTest ${EXTRA_LIBS})
endif(${UNITTEST})
#################################################


# Include mini-zip
if(not $ENV{INCLUDE_MINI_ZIP})
    target_compile_definitions(VectorworksMvrGdtf PUBLIC DONT_INCLUDE_MINI_ZIP)
endif(not $ENV{INCLUDE_MINI_ZIP})


# Additional options
set(CMAKE_EXE_LINKER_FLAGS  ${CMAKE_EXE_LINKER_FLAGS}
                            $ENV{ADDIONAL_LD})

add_compile_options($ENV{CXX_FLAGS_CUSTOM})

if($ENV{XERCES_CONFIGURE_ENCODER})
    add_compile_options($ENV{XERCES_CONFIGURE_ENCODER})
endif($ENV{XERCES_CONFIGURE_ENCODER})

# Flag CXX

