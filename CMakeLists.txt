SET(CMAKE_POLICY_DEFAULT_CMP0074 NEW)
cmake_minimum_required(VERSION 3.9.4)

# pre setup for some vars
set(UNITTEST FALSE CACHE BOOL "If enabled the tests wont be build!")
set(WIN_RUNTIME_LIB "-MD" CACHE STRING "Set '-MD' or '-MT' for windows build")
set(DO_NOT_INCLUDE_MINI_ZIP FALSE CACHE BOOL "Set whether or not we include the minzip lib")
set(BUILD_MVR_XCHANGE_EXAMPLE FALSE CACHE BOOL "Whether to or not to build the MVRXChange example. Mutually exclusive with DO_NOT_INCLUDE_MINI_ZIP")
set(DONT_USE_XERCES_AS_XMLLIB FALSE CACHE BOOL "Set whether or we use Xerces or tinyXML as xml lib")
set(BUILD_MVR_XCHANGE TRUE CACHE BOOL "Set whether to include MVR_XChange in the build (requires boost)")

set(XERCES_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../xerces-c CACHE STRING "Set the build path where you called cmake.")
set(XERCES_INCLUDE_PATH ${XERCES_ROOT_PATH}/src ${XERCES_ROOT_PATH}/build/src CACHE STRING "Set the include path")

if (${BUILD_MVR_XCHANGE} OR DEFINED ENV{BUILD_MVR_XCHANGE})
    add_compile_definitions(BUILD_MVR_XCHANGE)
endif()

if (${DONT_USE_XERCES_AS_XMLLIB} OR DEFINED ENV{DONT_USE_XERCES_AS_XMLLIB})
    add_compile_definitions(DONT_USE_XERCES_AS_XMLLIB)
else()
    if (WIN32)
    set(XERCES_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../xerces-c/build/src/Release/xerces-c_3.lib CACHE STRING "Set the xerces libary path")
    else()
    set(XERCES_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../xerces-c/build/src/libxerces-c-3.2.a CACHE STRING "Set the xerces libary path")
    endif(WIN32)
endif()

if(${BUILD_MVR_XCHANGE_EXAMPLE} AND ${DO_NOT_INCLUDE_MINI_ZIP} AND NOT ${BUILD_MVR_XCHANGE})
  message( FATAL_ERROR "MVRXChange example must be linked against Mini Zip and boost" )
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#################################################
# System setup
if (WIN32)
message("MSVC Runtime lib: " ${WIN_RUNTIME_LIB})
set(CMAKE_CXX_FLAGS_DEBUG ${WIN_RUNTIME_LIB}d)
set(CMAKE_CXX_FLAGS_RELEASE ${WIN_RUNTIME_LIB})
set(CMAKE_CXX_FLAGS_MINSIZEREL ${WIN_RUNTIME_LIB})
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${WIN_RUNTIME_LIB})
elseif(APPLE)
    if($ENV{OSX_VERSION})
    message("Setting osx version: " $ENV{OSX_VERSION})
        set(CMAKE_OSX_DEPLOYMENT_TARGET $ENV{OSX_VERSION})
    endif($ENV{OSX_VERSION})
endif(WIN32)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)


#################################################

add_subdirectory(mdns_cpp)

#################################################
# create the project
project(MvrGdtf)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)



# Set output dir

if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/)
endif()
if(NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src
                    ${XERCES_INCLUDE_PATH})

if(BUILD_MVR_XCHANGE)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../boost/
                        ${CMAKE_CURRENT_SOURCE_DIR}/mdns_cpp/include/)
endif()

# default values
# those can be removed probably
set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SRC_TESTDIR ${CMAKE_CURRENT_SOURCE_DIR}/unittest)






#################################################
# Add libMvrGdtf lib
file(GLOB_RECURSE libSourceFiles ${SRCDIR}/*.cpp)

if(NOT ${BUILD_MVR_XCHANGE})
    list(FILTER libSourceFiles EXCLUDE REGEX ".*/mvrxchange/.*")
endif()

add_library(MvrGdtf STATIC ${libSourceFiles})

if (NOT ${DONT_USE_XERCES_AS_XMLLIB} AND NOT DEFINED ENV{DONT_USE_XERCES_AS_XMLLIB})
    target_link_libraries(MvrGdtf ${XERCES_LIB_PATH})
endif()


if(${BUILD_MVR_XCHANGE})
    target_link_libraries(MvrGdtf mdns_cpp)
endif()
#################################################


#################################################
############### add unit tests ##################
if (UNITTEST)

file(GLOB_RECURSE unitTestSourceFiles ${SRC_TESTDIR}/*.cpp)
add_executable(MvrGdtfUnitTest ${unitTestSourceFiles})

add_definitions(-DGITPATH="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(MvrGdtfUnitTest MvrGdtf)
add_compile_definitions(IS_UNITTEST)
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

    set_target_properties( MvrGdtf PROPERTIES RUNTIME_OUTPUT_DIRECTORY    ${CMAKE_CURRENT_SOURCE_DIR}/libs/ )
    set_target_properties( MvrGdtf PROPERTIES LIBRARY_OUTPUT_DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/libs/ )
    set_target_properties( MvrGdtf PROPERTIES ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/libs/ )
elseif(ANDROID)
    set(PREPROCESSORS ${PREPROCESSORS} PUBLIC GS_LIN) # Use Linux imports for string related stuff
    set(PREPROCESSORS ${PREPROCESSORS} PUBLIC _ANDROID)
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

#Append Runtime
if (WIN32)
    get_target_property(OUTPUT_NAME_OLD MvrGdtfUnitTest OUTPUT_NAME)
    set(OUTPUT_NAME_OLD "${OUTPUT_NAME_OLD}${WIN_RUNTIME_LIB}")
    set_target_properties(MvrGdtfUnitTest PROPERTIES OUTPUT_NAME ${OUTPUT_NAME_OLD})
endif(WIN32)

endif(${UNITTEST})
#################################################


set(LIB_OUTPUT_NAME "MvrGdtf" CACHE STRING "The output name of the lib file")
set_target_properties(MvrGdtf PROPERTIES OUTPUT_NAME ${LIB_OUTPUT_NAME})

# Include mini-zip
if(${DO_NOT_INCLUDE_MINI_ZIP} OR DEFINED ENV{DO_NOT_INCLUDE_MINI_ZIP})
    target_compile_definitions(MvrGdtf PUBLIC DONT_INCLUDE_MINI_ZIP)

    get_target_property(OUTPUT_NAME_OLD MvrGdtf OUTPUT_NAME)
    set(OUTPUT_NAME_OLD "${OUTPUT_NAME_OLD}_NO_MZ")

    set_target_properties(MvrGdtf PROPERTIES OUTPUT_NAME ${OUTPUT_NAME_OLD})
endif()

if(${BUILD_MVR_XCHANGE_EXAMPLE})
    file(GLOB_RECURSE share_files examples/gdtf_share/*.cpp)
    add_executable(shareTest ${share_files})
    target_link_libraries(shareTest MvrGdtf)
    target_compile_definitions(shareTest ${PREPROCESSORS})
    target_link_libraries(shareTest ${EXTRA_LIBS})
endif()

if(${DONT_USE_XERCES_AS_XMLLIB} OR DEFINED ENV{DONT_USE_XERCES_AS_XMLLIB})
    target_compile_definitions(MvrGdtf PUBLIC DONT_USE_XERCES_AS_XMLLIB)
endif()

#Append Runtime
if (WIN32)
    get_target_property(OUTPUT_NAME_OLD MvrGdtf OUTPUT_NAME)
    set(OUTPUT_NAME_OLD "${OUTPUT_NAME_OLD}${WIN_RUNTIME_LIB}")
    set_target_properties(MvrGdtf PROPERTIES OUTPUT_NAME ${OUTPUT_NAME_OLD})
    set_target_properties(MvrGdtf PROPERTIES DEBUG_OUTPUT_NAME ${OUTPUT_NAME_OLD}d)
endif(WIN32)


# Additional options
set(CMAKE_EXE_LINKER_FLAGS  ${CMAKE_EXE_LINKER_FLAGS}
                            $ENV{ADDIONAL_LD})

add_compile_options($ENV{CXX_FLAGS_CUSTOM})

if($ENV{XERCES_CONFIGURE_ENCODER})
    add_compile_options($ENV{XERCES_CONFIGURE_ENCODER})
endif($ENV{XERCES_CONFIGURE_ENCODER})

# Flag CXX

