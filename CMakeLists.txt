cmake_minimum_required(VERSION 3.10)

# set the project name
project(MvrGdtf)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add libary
project(libMvrGdtf
${PROJECT_SOURCE_DIR}/src"
${PROJECT_SOURCE_DIR}/src/Implementation
${PROJECT_SOURCE_DIR}/src/sha256
${PROJECT_SOURCE_DIR}/src/Wrapper
${PROJECT_SOURCE_DIR}/src/XMLLib
)

# add the executable
add_executable(libMvrGdtfUnitTest 
)