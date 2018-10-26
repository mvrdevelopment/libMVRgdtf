##
##	Makefile for libVectorworksMvrGdtf
##


# set library name
TargetLibName	= libVectorworksMvrGdtf
TargetTestName	= vectorworksMvrGdtfTestApp


# folders
SRCDIR	= src
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
else
    UNAME_S := $(shell uname -s)
# Linux
    ifeq ($(UNAME_S),Linux)
		CXXFLAGS	+= -DGS_LIN=1 -MMD -MP 
		LDFLAGS		+= -DfPIC
		libExt		= .so
		#TODO -f for forced / without delete confirmation
		RM			= rm -r $(BINDIR)/*
    endif
# Mac
    ifeq ($(UNAME_S),Darwin)
		CXXFLAGS	+= -DGS_MAC=1 -MMD -MP 
		LDFLAGS		+= -DfPIC
		libExt		= .so
		#TODO -f for forced / without delete confirmation
		RM			= rm -r $(BINDIR)/*
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


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling objects for $(TargetLib) ..."
	if not exist $(OBJDIR) md $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $(SOURCES) -o $@


# Mac Linux
$(TargetLibName).so: $(SOURCES)
	@echo "Linking $(TargetLib) ..."
	mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) $(LDFLAGS) -o $(BINDIR)/$@ $(SOURCES)