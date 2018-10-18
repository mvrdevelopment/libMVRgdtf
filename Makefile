##
##	Makefile for libVectorworksMvrGdtf
##


# set library name
targetLibName	= libVectorworksMvrGdtf


# folders
SRCDIR	= src
OBJDIR	= obj
BINDIR	= bin


# compiler, linker and options
CXX			= g++					# gnu c++ compiler on all platforms
CXXFLAGS	= -g -std=c++11	-c		# compiler options
LDFLAGS		= -shared				# linker options


# set platform compiler, linker and e.t.c. options
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
		RM			= rm $(BINDIR)/*; rm $(OBJDIR)/*
    endif
# Mac
    ifeq ($(UNAME_S),Darwin)
		CXXFLAGS	+= -DGS_MAC=1 -MMD -MP 
		LDFLAGS		+= -DfPIC
		libExt		= .so
		#TODO -f for forced / without delete confirmation
		RM			= rm $(BINDIR)/*; rm $(OBJDIR)/*
    endif
endif

# This is then the end of Linker Flags, don't add more after this
LDFLAGS	+= -o


# What to compile and link
ifeq ($(OS),Windows_NT)
	SOURCES			= $(wildcard $(SRCDIR)/*.cpp)
	OBJECTSWIN		= $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))
else
	SOURCES			= $(shell echo $(SRCDIR)/*.cpp)
	OBJECTSMACLIN	= $(SOURCES:.cpp=.o)
endif


# Make Targets
targetLib = $(targetLibName)$(libExt)


# ALL
all: $(targetLib) UnitTestDLL.exe


# CLEAN
clean:
	@echo "Cleaning $(targetLib)...  "
	$(RM)

# Unit Test
# Windows
UnitTestDLL.exe: UnitTestDLL/UnitTestDLL.cpp
	@echo "Building UnitTestDLL.exe"
	$(CXX) -g -std=c++11 -DGS_WIN UnitTestDLL/UnitTestDLL.cpp -o bin/UnitTestDLL.exe -I$(SRCDIR)/ -L$(BINDIR) -l$(targetLibName)
	bin/UnitTestDLL.exe

# Build .dll/.so
# Windows
$(targetLibName).dll: $(OBJECTSWIN)
	@echo "Linking $(targetLib) ..."
	if not exist $(OBJDIR) md $(OBJDIR)
	$(CXX) $(LDFLAGS) $(BINDIR)/$@ $(OBJECTSWIN) -Wl,--out-implib,$(BINDIR)/$(targetLibName).lib


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling objects for $(targetLib) ..."
	if not exist $(OBJDIR) md $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@


# Mac Linux
$(targetLibName).so: $(OBJECTSMACLIN)
	@echo "Linking $(targetLib) ..."
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(BINDIR)/$(targetLib) $(OBJECTSMACLIN)