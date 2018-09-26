#################################################################
#																#
#	Makefile for libVectorworksMvrGdtf							#
#																#
#################################################################

# set library name
targetLibName	= libVectorworksMvrGdtf

# Folders
buildFolder = C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf

#-------------------------------------------------------------------------------------------------------------------------------
# set platform compiler and linker flags

# Windows
ifeq ($(OS),Windows_NT)
		CXX			= cl.exe			#c++ compiler
		CXXFLAGS	= /D_USRDLL /D_WINDLL /P
		CXXFLAGS	+= /DGS_WIN=1		
		LD			= link.exe				# linker
		libExt		= .dll

else
    UNAME_S := $(shell uname -s)

# Linux
    ifeq ($(UNAME_S),Linux)
        CXX			= g++				#c++ compiler and linker(gcc or ld)
		CXXFLAGS	= -g -std=c++11		#c++ compiler flags
		CXXFLAGS	+= -DGS_LIN=1
		LDFLAGS		= -shared -DfPIC	#linker flags
		libExt		= .so
    endif

# Mac
    ifeq ($(UNAME_S),Darwin)
		CXX			= g++				#c++ compiler and linker(gcc or ld)
		CXXFLAGS	= -g -std=c++11		#c++ compiler flags
		CXXFLAGS	+= -DGS_MAC=1
		LDFLAGS		= -shared -DfPIC	#linker flags
		libExt		= .so
    endif
endif

#-------------------------------------------------------------------------------------------------------------------------------
# What to compile
SOURCES = $(shell echo src/*.cpp)
HEADERS = $(shell echo src/*.h)
OBJECTS = $(SOURCES:.cpp=.o)


#-------------------------------------------------------------------------------------------------------------------------------
# Make Targets
targetLib = $(targetLibName)$(libExt)

# ALL
all: $(targetLib)

# Build targetLib
# Windows

$(targetLibName).dll: $(SOURCES)
	@echo Start to build lib on Win
	$(CXX) $(CXXFLAGS) src\GSString.cpp /MT /DLL /OUT:hello.lib


# Mac Linux
$(targetLibName).so: $(OBJECTS)
	@echo $(targetLibName)
	$(CXX) $(CXXFLAGS) -c -MMD -MP $(LDFLAGS) -o $(targetLib) $(OBJECTS)