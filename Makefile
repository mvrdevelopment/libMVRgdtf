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
		CXXFLAGS	+= -DGS_WIN=1 -DEXPORT_SYMBOLS=1 -D_WINDOWS
		libExt		= .dll
		RM			= if exist $(BINDIR)\* del /q $(BINDIR)\* & if exist $(OBJDIR)\* del /q $(OBJDIR)\*
		MV 			= move *.o $(OBJDIR)/
else
    UNAME_S := $(shell uname -s)
# Linux
    ifeq ($(UNAME_S),Linux)
		CXXFLAGS	+= -DGS_LIN=1 -MMD -MP -D_LINUX
		LDFLAGS		+= -DfPIC
		libExt		= .so
		#TODO -f for forced / without delete confirmation
		RM			= rm -rvf $(BINDIR)/*; rm -rvf $(OBJDIR)/*
		MV 			= mv *.o $(OBJDIR)/

    endif
# Mac
    ifeq ($(UNAME_S),Darwin)
		CXXFLAGS	+= -DGS_MAC=1 -MMD -MP -D__APPLE__
		LDFLAGS		+= -DfPIC
		libExt		= .so
		#TODO -f for forced / without delete confirmation
		RM			= rm -rvf $(BINDIR)/*; rm -rvf $(OBJDIR)/*
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
	OBJECTSMACLIN	= $(wildcard $(OBJDIR)/*.o)
endif


# Make Targets
TargetLib	= $(TargetLibName)$(libExt)
TargetTest	= $(TargetTestName)$(UnitTestExt) 

# ALL
all: $(TargetLib)

one: $(BINDIR)/test.so

# UnitTest
test: $(TargetTest)

# CLEAN
clean:
	@echo "Cleaning $(TargetLib)...  "
	$(RM)

# Unit Test
# Windows
# $(TargetTestName).exe: unittest/main.cpp
# 	@echo "Building $@ ..."
# 	$(CXX) $(CXXFLAGS) $(CXXFLAGSUNITTEST) unittest/main.cpp -o $(BINDIR)/$@ -I$(SRCDIR)/ -L$(BINDIR) -l$(TargetLibName)
# 	$(BINDIR)/$@

# # Mac Linux
# $(TargetTestName): unittest/main.cpp
# 	@echo "Building $@ ..."
# 	$(CXX) $(CXXFLAGS) $(CXXFLAGSUNITTEST) unittest/main.cpp -o $(BINDIR)/$@ -I$(SRCDIR)/ -L$(BINDIR)/ -lVectorworksMvrGdtf
# 	./$(BINDIR)/$@


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


# # Mac Linux
# $(TargetLibName).so: $(SOURCES) $(wildcard $(SRCDIR_IMPL)/*.cpp) $(wildcard $(SRCDIR_MZIP)/*.cpp) $(wildcard $(SRCDIR_S256)/*.cpp) $(wildcard $(SRCDIR_WRAP)/*.cpp) $(wildcard $(SRCDIR_XMLL)/*.cpp)
# 	@echo "Linking $(TargetLib) ..."
# 	mkdir -p $(BINDIR)
# 	$(CXX) $(CXXFLAGS) -I$(SRCDIR) $(LDFLAGS) -o $(BINDIR)/$@ $(SOURCES) $(wildcard $(SRCDIR_IMPL)/*.cpp) $(wildcard $(SRCDIR_MZIP)/*.cpp) $(wildcard $(SRCDIR_S256)/*.cpp) $(wildcard $(SRCDIR_WRAP)/*.cpp) $(wildcard $(SRCDIR_XMLL)/*.cpp)
# 	$(MV)


CPPFILES	= $(wildcard $(SRCDIR)/**/*.cpp)
HEADERFILES	= $(wildcard $(SRCDIR)/**/*.h)
OBJFILES := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CPPFILES))


SRC			= $(wildcard $(SRCDIR)/*.cpp)
SRC_IMPL	= $(wildcard $(SRCDIR_IMPL)/*.cpp)
SRC_MZIP	= $(wildcard $(SRCDIR_MZIP)/*.c)
SRC_S256	= $(wildcard $(SRCDIR_S256)/*.cpp)
SRC_WRAP	= $(wildcard $(SRCDIR_WRAP)/*.cpp)
SRC_XMLL	= $(wildcard $(SRCDIR_XMLL)/*.cpp)
OBJ			= $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
OBJ_IMPL	= $(patsubst $(SRCDIR_IMPL)/%.cpp, $(OBJDIR)/%.o, $(SRC_IMPL))
OBJ_MZIP	= $(patsubst $(SRCDIR_MZIP)/%.c, $(OBJDIR)/%.o, $(SRC_MZIP))
OBJ_S256	= $(patsubst $(SRCDIR_S256)/%.cpp, $(OBJDIR)/%.o, $(SRC_S256))
OBJ_WRAP	= $(patsubst $(SRCDIR_WRAP)/%.cpp, $(OBJDIR)/%.o, $(SRC_WRAP))
OBJ_XMLL	= $(patsubst $(SRCDIR_XMLL)/%.cpp, $(OBJDIR)/%.o, $(SRC_XMLL))
SOURCE		= $(SRC) $(SRC_IMPL) $(SRC_MZIP) $(SRC_S256) $(SRC_WRAP) $(SRC_XMLL)
OBJS		= $(OBJ) $(OBJ_IMPL) $(OBJ_MZIP) $(OBJ_S256) $(OBJ_WRAP) $(OBJ_XMLL)
VPATH 		= $(SRCDIR):$(SRCDIR_IMPL):$(SRCDIR_MZIP):$(SRCDIR_S256):$(SRCDIR_WRAP):$(SRCDIR_XMLL)

$(BINDIR)/test.so: $(OBJS)
	@echo "compile test.so for deniz with:"
	@echo ""
	@echo $(OBJS)
	@echo #######################################################"
	@echo "src/objs:"
	@echo ""
	@echo $(OBJ)


$(OBJS): | obj

obj:
	@echo "objdirwill be created if needed"
	@mkdir -p $(OBJDIR)

obj/%.o : %.cpp
	@echo "Compiling:	" $< 
	@$(CXX) $(CXXFLAGS) -I$(SRCDIR) -c $< -o $@