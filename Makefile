##
##	Makefile for libVectorworksMvrGdtf
##


# set library name
TargetLibName	= libVectorworksMvrGdtf
TargetTestName	= vectorworksMvrGdtfTestApp


# folders
SRCDIR		= src
SRCDIR_IMPL	= src/Implementation
SRCDIR_MZIP	= src/Minizip/Source
SRCDIR_S256	= src/sha256
SRCDIR_WRAP	= src/Wrapper
SRCDIR_XMLL	= src/XMLLib
OBJDIR	= obj
BINDIR	= bin


# compiler, linker and options
CXX			= g++					# gnu c++ compiler on all platforms
CXXFLAGS	= -g -std=c++11			# compiler options
LDFLAGS		= -shared				# linker options


# Library:	set platform compiler, linker and e.t.c. options
# Windows
ifeq ($(OS),Windows_NT)
		CXXFLAGS	+= -DGS_WIN=1 -DEXPORT_SYMBOLS=1
		libExt		= .dll
		RM			= if exist $(BINDIR)\* del /q $(BINDIR)\* & if exist $(OBJDIR)\* del /q $(OBJDIR)\*
		MV 			= move *.o $(OBJDIR)/
else
    UNAME_S := $(shell uname -s)
# Linux
    ifeq ($(UNAME_S),Linux)
		CXXFLAGS	+= -DGS_LIN=1 -MMD -MP 
		LDFLAGS		+= -DfPIC
		libExt		= .so
		#TODO -f for forced / without delete confirmation
		RM			= rm -r $(BINDIR)/*
		MV 			= mv *.o $(OBJDIR)/

    endif
# Mac
    ifeq ($(UNAME_S),Darwin)
		CXXFLAGS	+= -DGS_MAC=1 -MMD -MP 
		LDFLAGS		+= -DfPIC
		libExt		= .so
		#TODO -f for forced / without delete confirmation
		RM			= rm -r $(BINDIR)/*
		MV 			= mv *.o $(OBJDIR)/
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


# What to compile and link
ifeq ($(OS),Windows_NT)
	SOURCES			= $(wildcard $(SRCDIR)/*.cpp)
	HEADERS			= $(wildcard $(SRCDIR)/*.h)
	OBJECTSWIN		= $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
else
	SOURCES			= $(shell echo $(SRCDIR)/*.cpp)
	OBJECTSMACLIN	= $(SOURCES:.cpp=.o)
endif


# Make Targets
TargetLib	= $(TargetLibName)$(libExt)
TargetTest	= $(TargetTestName)$(UnitTestExt) 

# ALL
all: $(TargetLib)

# UnitTest
test: $(TargetTest)

# CLEAN
clean:
	@echo "Cleaning $(TargetLib)...  "
	$(RM)

# Unit Test
# Windows
$(TargetTestName).exe: unittest/main.cpp
	@echo "Building $@ ..."
	$(CXX) $(CXXFLAGS) $(CXXFLAGSUNITTEST) unittest/main.cpp -o $(BINDIR)/$@ -I$(SRCDIR)/ -L$(BINDIR) -l$(TargetLibName)
	$(BINDIR)/$@

# Mac Linux
$(TargetTestName): unittest/main.cpp
	@echo "Building $@ ..."
	$(CXX) $(CXXFLAGS) $(CXXFLAGSUNITTEST) unittest/main.cpp -o $(BINDIR)/$@ -I$(SRCDIR)/ -L$(BINDIR)/ -lVectorworksMvrGdtf
	./$(BINDIR)/$@


# Build .dll/.so
# Windows
$(TargetLibName).dll: $(OBJECTSWIN)
	@echo "Linking $(TargetLib) ..."
	if not exist $(BINDIR) md $(BINDIR)
	$(CXX) $(LDFLAGS) -o $(BINDIR)/$@ $(OBJECTSWIN) -Wl,--out-implib,$(BINDIR)/$(TargetLibName).lib


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(wildcard $(SRCDIR_IMPL)/*.cpp)
	@echo "Compiling objects for $(TargetLib) ..."
	if not exist $(OBJDIR) md $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $(SOURCES) $(wildcard $(SRCDIR_IMPL)/*.cpp)
	$(MV)


# Mac Linux
$(TargetLibName).so: $(SOURCES)
	@echo "Linking $(TargetLib) ..."
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -c $(LDFLAGS) -o $(BINDIR)/$@ $(SOURCES)
	$(MV)