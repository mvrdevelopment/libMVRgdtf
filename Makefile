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
LDFLAGS		= -shared -fPic			#linker flags

#platform flags
CXXFLAGS	+= -DGS_LIN=1

# define the dirs that are used here
root      	= $(CURDIR)/
sourcedir 	= $(root)src/
objectdir 	= $(root)objects/
executedir	= $(root)

#-------------------------------------------------------------------------------------------------------------------------------
# Generate the VPATH
vpath %.cpp $(sourcedir)
vpath %.h $(sourcedir)
vpath %.o $(objectdir)

# Object list
objects 	= GSString.o GSString.X.o GSTypes.o GSUtil.o 

# Files 
# !!!! check necessarity !!!!
GSString.o 		: GSString.h StdHeaders.h
GSString.X.o 	: GSString.X.h
GSTypes.o 		: GSTypes.h
GSUtil.o 		: GSUtil.h


#-------------------------------------------------------------------------------------------------------------------------------
# Make Targets

# ALL
# !!!! What's the difference between make / make all?  !!!!
.PHONY: all
all: $(targetLib)

# CLEAN
.PHONY: clean
clean:
	rm $(objectdir)*
	@echo "		Cleaning done."

# Default Target
$(targetLib):
	mkdir -p objects
	$(objects)
	@echo "		Linking..."
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(executedir)(notdir $@)$(patsubst %.cpp,$(objectdir)%.o,$(objects)) $(executedir)(notdir $^)

# Compile the cpp
%.o : %.cpp
	@echo "		Compiling source: "$(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -o $(objectdir)$(notdir $@) $(sourcedir)$(notdir $<) 
