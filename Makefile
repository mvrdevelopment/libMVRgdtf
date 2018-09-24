#################################################################
#																#
#	Makefile for libVectorworksMvrGdtf							#
#																#
#################################################################

# set library name
targetLibName	= libVectorworksMvrGdtf

#-------------------------------------------------------------------------------------------------------------------------------
# set platform compiler and linker flags

# Windows
ifeq ($(OS),Windows_NT)
		CXX			= cl.exe			#c++ compiler
		CXXFLAGS	+= -DGS_WIN=1
		libExt		= .dll

else
    UNAME_S := $(shell uname -s)

# Linux
    ifeq ($(UNAME_S),Linux)
        CXX			= g++				#c++ compiler and linker(gcc or ld)
		CXXFLAGS	= -g -std=c++11		#c++ compiler flags
		CXXFLAGS	+= -DGS_LIN=1
		LDFLAGS		= -shared 			#linker flags
		LDFLAGS		= -DfPIC 
		libExt		= .so
    endif

# Mac
    ifeq ($(UNAME_S),Darwin)
		CXX			= g++				#c++ compiler and linker(gcc or ld)
		CXXFLAGS	= -g -std=c++11		#c++ compiler flags
		CXXFLAGS	+= -DGS_MAC=1
		LDFLAGS		= -shared 			#linker flags
		libExt		= .so
    endif
endif

# update library name with extension
targetLib	= $(targetLibName)$(libExt)

#-------------------------------------------------------------------------------------------------------------------------------
# What to compile
SOURCES = $(shell echo src/*.cpp)
HEADERS = $(shell echo src/*.h)
OBJECTS = $(SOURCES:.c=.o)


#-------------------------------------------------------------------------------------------------------------------------------
# Make Targets

#----------------------------
# Testing
$(info $(targetLib))
$(info $(OS))
$(info $(UNAME_S))
#----------------------------

# ALL
all: $(targetLib)

# Build targetLib
$(targetLib): $(OBJECTS)
	cl.exe $(CXXFLAGS) -c -MMD -MP $(LDFLAGS) -o $(targetLib) $(OBJECTS)
		