##
##	Makefile for libVectorworksMvrGdtf
##


# set library name
TargetLibName	= libVectorworksMvrGdtf
TargetTestName	= vectorworksMvrGdtfTestApp


# folders
SRCDIR		= src
SRCDIR_IMPL	= src/Implementation
SRCDIR_S256	= src/sha256
SRCDIR_WRAP	= src/Wrapper
SRCDIR_XMLL	= src/XMLLib
OBJDIR		= obj
BINDIR		= bin


# compiler, linker and options
CXX			= g++					# gnu c++ compiler on all platforms
CXXFLAGS	= -g -std=c++11			# compiler options
LDFLAGS		= -shared				# linker options


XERCESLIBNAME	=
XERCESLIBPATH	=

# Library: set platform compiler, linker and e.t.c. options
# Windows
ifeq ($(OS),Windows_NT)
		CXXFLAGS	+= -DGS_WIN=1 -DEXPORT_SYMBOLS=1 -D_WINDOWS
		libExt		= .dll
		RM			= if exist $(BINDIR)\* del /q $(BINDIR)\* & if exist $(OBJDIR)\* del /q $(OBJDIR)\*
		MV 			= move *.o $(OBJDIR)/
else
    UNAME_S := $(shell uname -s)
# Linux
    ifeq ($(UNAME_S),Linux)
		CXXFLAGS	+= -DGS_LIN=1 -MMD -MP -fPIC -D_LINUX
		LDFLAGS		+=
		libExt		= .so
		RM			= rm -rf $(BINDIR)/*; rm -rf $(OBJDIR)/*
		XERCESLIBNAME	=
		XERCESLIBPATH	= 
    endif
# Mac
    ifeq ($(UNAME_S),Darwin)
		CXXFLAGS	+= -DGS_MAC=1 -MMD -MP -fPIC -D__APPLE__
		LDFLAGS		+=
		libExt		= .so
		RM			= rm -rf $(BINDIR)/*; rm -rf $(OBJDIR)/*
		XERCESLIBNAME	= xerces-c
		XERCESLIBPATH	= ./libs/mac/release/
    endif
endif


# UnitTest:	set platform compiler, linker and e.t.c. options
# Windows
ifeq ($(OS),Windows_NT)
		CXXFLAGSUNITTEST	+= -DGS_WIN=1
		UnitTestExt			= .exe
else
    UNAME_S := $(shell uname -s)
# Linux
    ifeq ($(UNAME_S),Linux)
		CXXFLAGSUNITTEST	+= -DGS_LIN=1 -MMD -MP
		UnitTestExt			=
    endif
# Mac
    ifeq ($(UNAME_S),Darwin)
		CXXFLAGSUNITTEST	+= -DGS_MAC=1 -MMD -MP
		UnitTestExt			=
    endif
endif


# deprecated maybe, let's see because of windows vsproj-generation 
#
# # What to compile and link
# ifeq ($(OS),Windows_NT)
# 	SOURCES			= $(wildcard $(SRCDIR)/*.cpp)
# 	HEADERS			= $(wildcard $(SRCDIR)/*.h)
# 	OBJECTSWIN		= $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
# else
# 	SOURCES			= $(shell echo $(SRCDIR)/*.cpp)
# 	OBJECTSMACLIN	= $(wildcard $(OBJDIR)/*.o)
# endif


# sources and objects
SRC			= $(wildcard $(SRCDIR)/*.cpp)
SRC_IMPL	= $(wildcard $(SRCDIR_IMPL)/*.cpp)
SRC_S256	= $(wildcard $(SRCDIR_S256)/*.cpp)
SRC_WRAP	= $(wildcard $(SRCDIR_WRAP)/*.cpp)
SRC_XMLL	= $(wildcard $(SRCDIR_XMLL)/*.cpp)
OBJ			= $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
OBJ_IMPL	= $(patsubst $(SRCDIR_IMPL)/%.cpp, $(OBJDIR)/%.o, $(SRC_IMPL))
OBJ_S256	= $(patsubst $(SRCDIR_S256)/%.cpp, $(OBJDIR)/%.o, $(SRC_S256))
OBJ_WRAP	= $(patsubst $(SRCDIR_WRAP)/%.cpp, $(OBJDIR)/%.o, $(SRC_WRAP))
OBJ_XMLL	= $(patsubst $(SRCDIR_XMLL)/%.cpp, $(OBJDIR)/%.o, $(SRC_XMLL))
SOURCES		= $(SRC) $(SRC_IMPL) $(SRC_S256) $(SRC_WRAP) $(SRC_XMLL)
OBJECTS		= $(OBJ) $(OBJ_IMPL) $(OBJ_S256) $(OBJ_WRAP) $(OBJ_XMLL)


# place where to look for %.cpp for generic rule $(OBJDIR)/%.o : %.cpp
VPATH 		= $(SRCDIR):$(SRCDIR_IMPL):$(SRCDIR_S256):$(SRCDIR_WRAP):$(SRCDIR_XMLL)


# Make Targets
TargetLib	= $(TargetLibName)$(libExt)
TargetTest	= $(TargetTestName)$(UnitTestExt) 

# ALL
all: $(TargetLib) $(TargetTestName)

# UnitTest
test: $(TargetTest)

# Xerces Build
xerces: 

# CLEAN
clean:
	@echo "Cleaning $(BINDIR)/ and $(OBJDIR)/ ...  "
	$(RM)


# Unit Test
# Windows
$(TargetTestName).exe: unittest/main.cpp
	@echo "Building $@ ..."
	$(CXX) $(CXXFLAGS) $(CXXFLAGSUNITTEST) $< -o $(BINDIR)/$@ -I$(SRCDIR)/ -L$(BINDIR) -l$(TargetLibName)
	$(BINDIR)/$@

# Mac Linux
$(TargetTestName): unittest/main.cpp
	@echo "Building $@ ..."
	$(CXX) $(CXXFLAGSUNITTEST) $< -o $(BINDIR)/$@ -I$(SRCDIR) -L$(BINDIR)/ -lVectorworksMvrGdtf
	./$(BINDIR)/$@


# Build .dll/.so
# Windows
# $(TargetLibName).dll: $(OBJECTSWIN)
# 	@echo "Linking $(TargetLib) ..."
# 	if not exist $(BINDIR) md $(BINDIR)
# 	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $(OBJECTSWIN) -Wl,--out-implib,$(BINDIR)/$(TargetLibName).lib


# $(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(wildcard $(SRCDIR_IMPL)/*.cpp) $(wildcard $(SRCDIR_MZIP)/*.cpp) $(wildcard $(SRCDIR_S256)/*.cpp) $(wildcard $(SRCDIR_WRAP)/*.cpp) $(wildcard $(SRCDIR_XMLL)/*.cpp)
# 	@echo "Compiling objects for $(TargetLib) ..."
# 	if not exist $(OBJDIR) md $(OBJDIR)
# 	$(CXX) $(CXXFLAGS) -Wfatal-errors -I$(SRCDIR) -c $(SOURCES) $(wildcard $(SRCDIR_IMPL)/*.cpp) $(wildcard $(SRCDIR_MZIP)/*.cpp) $(wildcard $(SRCDIR_S256)/*.cpp) $(wildcard $(SRCDIR_WRAP)/*.cpp) $(wildcard $(SRCDIR_XMLL)/*.cpp)
# 	$(MV)


# Mac Linux
$(TargetLibName).so: $(OBJECTS)
	@echo "Linking objects to $(TargetLib) ..."
	@mkdir -p $(BINDIR)
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $(OBJECTS) -L$(XERCESLIBPATH) -l$(XERCESLIBNAME)

$(OBJDIR)/%.o : %.cpp
	@echo "Compiling:	" $<
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@

# Include Header-Dependencies (stored as ".d" Makefile fragments files
# THIS MUST BE THE LAST SECTION OF THIS MAKEFILE, OTHERWISE YOU RISK OUT-OF-DATE OBJECTS GETTING LINKED
-include $(OBJECTS:.o=.d)