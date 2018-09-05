#################################################################
#																#
#	Makefile for libVectorworksMvrGdtf							#
#																#
#################################################################

# set library name
targetLib 	= libVectorworksMvrGdtf.so

# set paths and compiler flags
CXX			= g++				#c++ compiler
CXXFLAGS	= -g -std=c++11		#c++ compiler flags
LDFLAGS		= -shared 			#linker flags

UNAME_S := $(shell uname -s)
#platform flags
ifeq ($(UNAME_S), Linux)
CXXFLAGS	+= -DGS_LIN=1
LDFLAGS		= -DfPIC 		
endif
ifeq ($(UNAME_S), Darwin)
CXXFLAGS	+= -DGS_MAC=1
endif

#-------------------------------------------------------------------------------------------------------------------------------
# What to compile
SOURCES = $(shell echo src/*.cpp)
HEADERS = $(shell echo src/*.h)
OBJECTS = $(SOURCES:.c=.o)


#-------------------------------------------------------------------------------------------------------------------------------
# Make Targets

# ALL
all: $(targetLib)

# Build targetLib
$(targetLib): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -c -MMD -MP $(LDFLAGS) -o $(targetLib) $(OBJECTS)
