#################################################################
#								#
#	Makefile for libVectorworksMvrGdtf			#
#								#
#################################################################

# set library name
targetLib 	= libVectorworksMvrGdtf.so


# set paths and compiler flags
CXX			= g++				#c++ compiler
CXXFLAGS	= -c -g -std=c++11	#c++ compiler flags
LDFLAGS		= -shared			#linker flags

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
GSString.o 		: GSString.h StdHeaders.h
GSString.X.o 	: GSString.X.h
GSTypes.o 		: GSTypes.h
GSUtil.o 		: GSUtil.h


#-------------------------------------------------------------------------------------------------------------------------------
# Make Targets

# ALL
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
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(executedir)(notdir $^) -o $(executedir)(notdir $@)$(patsubst %.o,$(objectdir)%.o,$(objects))

# Compile the cpp
%.o : %.cpp
	@echo "		Compiling source: "$(notdir $<)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $(sourcedir)$(notdir $<) -o $(objectdir)$(notdir $@)
