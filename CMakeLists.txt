SET(CMAKE_POLICY_DEFAULT_CMP0074 NEW)
cmake_minimum_required(VERSION 3.9.4)

# pre setup for some vars
set(UNITTEST FALSE CACHE STRING "If enabled the tests wont be build!")
set(WIN_RUNTIME_LIB "-MD" CACHE STRING "Set '-MD' or '-MT' for windows build")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#################################################
# System setup
if (WIN32)
set(CMAKE_GENERATOR_PLATFORM x64)
message("MSVC Runtime lib: " ${WIN_RUNTIME_LIB})
set(CMAKE_CXX_FLAGS_RELEASE ${WIN_RUNTIME_LIB})
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


# setup the platform macros
set(XERCES_INCLUDE ${XERCES_INCLUDE} ${PROJECT_SOURCE_DIR}/../xerces-c/src/)
set(XERCES_INCLUDE ${XERCES_INCLUDE} ${PROJECT_SOURCE_DIR}/../xerces-c/build/src/)

if (WIN32)
set(XERCES_LIB ${PROJECT_SOURCE_DIR}/../xerces-c/build/src/libxerces-c-3.2.lib)
else()
set(XERCES_LIB ${PROJECT_SOURCE_DIR}/../xerces-c/build/src/libxerces-c-3.2.a)
endif(WIN32)



include_directories(${PROJECT_SOURCE_DIR}/src
                    ${XERCES_INCLUDE})

# default values
# those can be removed probably
set(SRCDIR ${PROJECT_SOURCE_DIR}/src)
set(SRC_TESTDIR ${PROJECT_SOURCE_DIR}/unittest)






#################################################
# Add libMvrGdtf lib
file(GLOB_RECURSE libSourceFiles ${SRCDIR}/*.cpp)
add_library(MvrGdtf STATIC ${libSourceFiles})

target_link_libraries(MvrGdtf ${XERCES_LIB})
#################################################


#################################################
############### add unit tests ##################
if (UNITTEST)

file(GLOB_RECURSE unitTestSourceFiles ${SRC_TESTDIR}/*.cpp)
add_executable(MvrGdtfUnitTest ${unitTestSourceFiles})

add_definitions(-DGITPATH="${PROJECT_SOURCE_DIR}")

target_link_libraries(MvrGdtfUnitTest MvrGdtf)
target_link_libraries(MvrGdtfUnitTest ${XERCES_LIB})

endif (UNITTEST)
#################################################



#################################################
# setup the platform macros
if (WIN32)
    set(PREPROCESSORS ${PREPROCESSORS} PUBLIC GS_WIN)
    set(PREPROCESSORS ${PREPROCESSORS} PUBLIC _WINDOWS)
    set(PREPROCESSORS ${PREPROCESSORS} PUBLIC EXPORT_STATIC)
    set(PREPROCESSORS ${PREPROCESSORS} PUBLIC LIBMvrGdtf_EXPORTS)
    
    
    set(EXTRA_LIBS ${EXTRA_LIBS} rpcrt4)
    set(EXTRA_LIBS ${EXTRA_LIBS} shlwapi)

    set_target_properties( MvrGdtf PROPERTIES RUNTIME_OUTPUT_DIRECTORY    ${PROJECT_SOURCE_DIR}/libs/ )
    set_target_properties( MvrGdtf PROPERTIES LIBRARY_OUTPUT_DIRECTORY   ${PROJECT_SOURCE_DIR}/libs/ )
    set_target_properties( MvrGdtf PROPERTIES ARCHIVE_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/libs/ )
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
target_compile_definitions(MvrGdtf ${PREPROCESSORS})
target_link_libraries(MvrGdtf ${EXTRA_LIBS})

if(${UNITTEST})
target_compile_definitions(MvrGdtfUnitTest ${PREPROCESSORS})
target_link_libraries(MvrGdtfUnitTest ${EXTRA_LIBS})
endif(${UNITTEST})
#################################################


set(LIB_OUTPUT_NAME "MvrGdtf")
set_target_properties(MvrGdtf PROPERTIES OUTPUT_NAME ${LIB_OUTPUT_NAME})

# Include mini-zip
if($ENV{DO_NOT_INCLUDE_MINI_ZIP})
    message("MINIZIP is not part of the symbols")
    target_compile_definitions(MvrGdtf PUBLIC DONT_INCLUDE_MINI_ZIP)

    get_target_property(OUTPUT_NAME_OLD MvrGdtf OUTPUT_NAME)
    set(OUTPUT_NAME_OLD "${OUTPUT_NAME_OLD}_NO_MZ")

    set_target_properties(MvrGdtf PROPERTIES OUTPUT_NAME ${OUTPUT_NAME_OLD})
endif($ENV{DO_NOT_INCLUDE_MINI_ZIP})

#Append Runtime
if (WIN32)
    get_target_property(OUTPUT_NAME_OLD MvrGdtf OUTPUT_NAME)
    set(OUTPUT_NAME_OLD "${OUTPUT_NAME_OLD}${WIN_RUNTIME_LIB}")
    set_target_properties(MvrGdtf PROPERTIES OUTPUT_NAME ${OUTPUT_NAME_OLD})
endif(WIN32)


# Additional options
set(CMAKE_EXE_LINKER_FLAGS  ${CMAKE_EXE_LINKER_FLAGS}
                            $ENV{ADDIONAL_LD})

add_compile_options($ENV{CXX_FLAGS_CUSTOM})

if($ENV{XERCES_CONFIGURE_ENCODER})
    add_compile_options($ENV{XERCES_CONFIGURE_ENCODER})
endif($ENV{XERCES_CONFIGURE_ENCODER})

# Flag CXX

