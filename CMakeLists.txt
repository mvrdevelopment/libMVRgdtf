cmake_minimum_required(VERSION 3.10)

if (WIN32)
set(CMAKE_GENERATOR_PLATFORM x64)
elseif(APPLE)
    if($ENV{OSX_VERSION})
    message("Setting osx version: " $ENV{OSX_VERSION})
        set(CMAKE_OSX_DEPLOYMENT_TARGET $ENV{OSX_VERSION})
    endif($ENV{OSX_VERSION})
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
set(SRC_TESTDIR ${PROJECT_SOURCE_DIR}/unittest)







# Add libary
# source files
file(GLOB_RECURSE libSourceFiles ${SRCDIR}/*.cpp)
add_library(VectorworksMvrGdtf STATIC ${libSourceFiles})

target_link_libraries(VectorworksMvrGdtf ${PROJECT_SOURCE_DIR}/libs/libxerces-c.a)


#################################################
############### add unit tests ##################
file(GLOB_RECURSE unitTestSourceFiles ${SRC_TESTDIR}/*.cpp)
add_executable(MvrGdtfUnitTest  ${unitTestSourceFiles})

add_definitions(-DGITPATH="${PROJECT_SOURCE_DIR}")
target_link_libraries(MvrGdtfUnitTest VectorworksMvrGdtf)
#add_dependencies(MvrGdtfUnitTest VectorworksMvrGdtf)
#################################################


# setup the platform macros
if (WIN32)
    target_compile_definitions(VectorworksMvrGdtf PUBLIC GS_WIN)
    target_compile_definitions(VectorworksMvrGdtf PUBLIC _WINDOWS)

    target_compile_definitions(MvrGdtfUnitTest PUBLIC GS_WIN)
    target_compile_definitions(MvrGdtfUnitTest PUBLIC _WINDOWS)
elseif(UNIX)
    if (APPLE)
        target_compile_definitions(VectorworksMvrGdtf PUBLIC GS_MAC)
        
        target_compile_definitions(MvrGdtfUnitTest PUBLIC GS_MAC)

        find_library( MAC_CORESERVICE CoreServices )
        find_library( MAC_COREFOUNDATION CoreFoundation )

        target_link_libraries(VectorworksMvrGdtf ${MAC_CORESERVICE} ${MAC_COREFOUNDATION})
        target_link_libraries(MvrGdtfUnitTest ${MAC_CORESERVICE} ${MAC_COREFOUNDATION})
    else()
        target_compile_definitions(VectorworksMvrGdtf PUBLIC GS_LIN)
        target_compile_definitions(VectorworksMvrGdtf PUBLIC _LINUX)

        target_compile_definitions(MvrGdtfUnitTest PUBLIC GS_LIN)
        target_compile_definitions(MvrGdtfUnitTest PUBLIC _LINUX)



        target_link_libraries(VectorworksMvrGdtf uuid)
        target_link_libraries(MvrGdtfUnitTest    uuid)
        #add_compile_definitions(GS_LIN)        
    endif(APPLE)


    target_link_libraries(VectorworksMvrGdtf    pthread)
    target_link_libraries(MvrGdtfUnitTest       pthread)
endif(WIN32)

# Include mini-zip
if(not $ENV{INCLUDE_MINI_ZIP})
    target_compile_definitions(VectorworksMvrGdtf PUBLIC DONT_INCLUDE_MINI_ZIP)
endif(not $ENV{INCLUDE_MINI_ZIP})

set(CMAKE_EXE_LINKER_FLAGS  ${CMAKE_EXE_LINKER_FLAGS}
                            $ENV{ADDIONAL_LD})

add_compile_options($ENV{CXX_FLAGS_CUSTOM})

if($ENV{XERCES_CONFIGURE_ENCODER})
    add_compile_options($ENV{XERCES_CONFIGURE_ENCODER})
endif($ENV{XERCES_CONFIGURE_ENCODER})


# Flag DDONT_INCLUDE_MINI_ZIP   -check
# Flag OSX_VERSION              -check
# Flag CXX

# CXX_FLAGS_CUSTOM              -check
# XERCES_CONFIGURE_ENCODER      -check
# ADDIONAL_LD                   -check
