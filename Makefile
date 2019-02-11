##
##	Makefile for libVectorworksMvrGdtf
##


# set library name
TargetLibName	= VectorworksMvrGdtf
TargetTestName	= vectorworksMvrGdtfTestApp


# folders
SRCDIR		= src
SRCDIR_IMPL	= src/Implementation
SRCDIR_S256	= src/sha256
SRCDIR_WRAP	= src/Wrapper
SRCDIR_XMLL	= src/XMLLib
SRCDIR_UNIT = unittest
OBJDIR		= obj
BINDIR		= x64/Release
LIBDIR_PRE	= libs
LIBDIR_POST	= release

# compiler, linker and options
CXX					?= g++									# gnu c++ compiler on all platforms
CXXFLAGS			= -std=c++11							# compiler options
CXXFLAGSUNITTEST	= -std=c++11	-DGITPATH=\"$(CURDIR)\"	# compiler options unit test
#LDFLAGS			= -shared								# linker options


XERCESLIBNAME	=
XERCESLIBPATH	=

LINKWITHLIBS    =

# Optimization levels and Debug behavoir
DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CXXFLAGS 			+= -g
	CXXFLAGSUNITTEST 	+= -g
else
    CXXFLAGS 			+= -O3 -Wall -Werror
	CXXFLAGSUNITTEST 	+= -O3
endif

# OSX defaults
OSX_VERSION		?= 10.10

# Library: set platform compiler, linker and e.t.c. options
# Windows
ifeq ($(OS),Windows_NT)
		CXXFLAGS		+= -DGS_WIN=1 -DEXPORT_SYMBOLS=1 -D_WINDOWS
		libExt			= .dll
		RM				= if exist $(BINDIR)\* del /q $(BINDIR)\* & if exist $(OBJDIR)\* del /q $(OBJDIR)\*
		MV 				= move *.o $(OBJDIR)/
else
    UNAME_S := $(shell uname -s)
# Linux
    ifeq ($(UNAME_S),Linux)
		CXXFLAGS		+= -DGS_LIN=1 -D_LINUX -MMD -MP -fPIC
		LDFLAGS			+=
		libExt			= .a
		LIBDIR_PLAT		= lin
		XERCESLIBNAME	= xerces-c
		LIBPATH			= libs/lin/release
		LINKWITHLIBS 	+= -luuid -lpthread
		RM				= rm -rf $(BINDIR)/*; rm -rf $(OBJDIR)/*; \
						rm -f $(LIBDIR_PRE)/$(LIBDIR_PLAT)/$(LIBDIR_POST)/lib$(TargetLib)
    endif
# Mac
    ifeq ($(UNAME_S),Darwin)
		CXXFLAGS		+= -DGS_MAC=1 -D__APPLE__ -MMD -MP -mmacosx-version-min=$(OSX_VERSION)
		LDFLAGS			+=
		libExt			= .a
		LIBDIR_PLAT		= mac
		XERCESLIBNAME	= Xerces
		LIBPATH			= libs/mac/release
		LINKWITHLIBS 	+= -lpthread -framework CoreServices -framework CoreFoundation
		RM				= rm -rf $(BINDIR)/*; rm -rf $(OBJDIR)/*; \
						rm -f $(LIBDIR_PRE)/$(LIBDIR_PLAT)/$(LIBDIR_POST)/lib$(TargetLib)
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
		CXXFLAGSUNITTEST	+= -DGS_LIN=1 -D_LINUX -MMD -MP
		UnitTestExt			=
    endif
# Mac
    ifeq ($(UNAME_S),Darwin)
		CXXFLAGSUNITTEST	+= -DGS_MAC=1 -D__APPLE__ -MMD -MP -mmacosx-version-min=$(OSX_VERSION)
		UnitTestExt			=
    endif
endif


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

SRC_UNIT	= $(wildcard $(SRCDIR_UNIT)/*.cpp)
OBJ_UNIT	= $(patsubst $(SRCDIR_UNIT)/%.cpp, $(OBJDIR)/%.o, $(SRC_UNIT))

# place where to look for %.cpp for generic rule $(OBJDIR)/%.o : %.cpp
VPATH 		= $(SRCDIR):$(SRCDIR_IMPL):$(SRCDIR_S256):$(SRCDIR_WRAP):$(SRCDIR_XMLL)


# Make Targets
TargetLib	= $(TargetLibName)$(libExt)
TargetTest	= $(TargetTestName)$(UnitTestExt) 

# ALL
all: $(TargetLib)

# UnitTest
test: $(TargetTest)

# Xerces Build
xerces: 

# CLEAN
clean:
	@echo "Cleaning $(BINDIR)/ and $(OBJDIR)/ ...  "
	$(RM)

# Mac Linux
$(TargetTestName): $(SRC_UNIT)
	@echo "Building $@ ..."
	@echo $(SRC_UNIT)
	$(CXX) $(CXXFLAGSUNITTEST) $^ -o $(BINDIR)/$@ -I$(SRCDIR) -L$(LIBPATH) -l$(TargetLibName) -l$(XERCESLIBNAME) $(LINKWITHLIBS)
	@./$(BINDIR)/$@

# Mac Linux
$(TargetLibName).a: $(OBJECTS)
	@echo "Linking objects to lib$(TargetLib) ..."
	@mkdir -p $(BINDIR)
	ar rcs $(LIBDIR_PRE)/$(LIBDIR_PLAT)/$(LIBDIR_POST)/lib$@ $(OBJECTS)
	@#$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $(OBJECTS) -L$(XERCESLIBPATH) -l$(XERCESLIBNAME) $(LINKWITHLIBS)

$(OBJDIR)/%.o : %.cpp
	@echo "Compiling:	" $<
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@


# Include Header-Dependencies (stored as ".d" Makefile fragments files
# THIS MUST BE THE LAST SECTION OF THIS MAKEFILE, OTHERWISE YOU RISK OUT-OF-DATE OBJECTS GETTING LINKED
-include $(OBJECTS:.o=.d)