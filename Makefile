##
##	Makefile for libVectorworksMvrGdtf
##

# set library name
targetLibName	= libVectorworksMvrGdtf

# folders
SRCDIR	= src
BINDIR	= bin

# compiler, linker and options
CXX			= g++					# gnu c++ compiler on all platforms
CXXFLAGS	= -g -std=c++11			# compiler options
LDFLAGS		= -shared -DfPIC		# linker options

# set platform compiler and linker flags
# Windows
ifeq ($(OS),Windows_NT)
		CXXFLAGS	+= -DGS_WIN=1 -DEXPORT_SYMBOLS=1
		libExt		= .dll
		RM			= del /s /q $(BINDIR)\*.dll & del /s /q $(BINDIR)\*.d
else
    UNAME_S := $(shell uname -s)
# Linux
    ifeq ($(UNAME_S),Linux)
		CXXFLAGS	+= -DGS_LIN=1
		libExt		= .so
		RM			= rm -rf bin/*.so	
    endif
# Mac
    ifeq ($(UNAME_S),Darwin)
		CXXFLAGS	+= -DGS_MAC=1
		libExt		= .so
		RM			= rm -rf bin/*.so	
    endif
endif

# What to compile
	SOURCES = $(shell echo src/*.cpp)


# Make Targets
targetLib = $(targetLibName)$(libExt)

# ALL
all: $(targetLib)

# CLEAN
clean:
	@echo "Cleaning $(targetLib)...  "
	$(RM)

# Build targetLib
# Windows
$(targetLibName).dll: $(SOURCES)
	@echo Start to build lib on Win
	if not exist bin md bin
	$(CXX) $(CXXFLAGS) -c -MMD -MP $(LDFLAGS) -o $(BINDIR)/$(targetLib) $(SOURCES)

# Mac Linux
$(targetLibName).so: $(OBJECTS)
	@echo $(targetLibName)
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c -MMD -MP $(LDFLAGS) -o $(BINDIR)$/(targetLib) $(OBJECTS)