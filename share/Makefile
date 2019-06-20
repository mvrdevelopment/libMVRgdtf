MAINDIR=../
include ../Makefile.defs

all: xerces

dir:
	@Create the directory for the share programs
	@ if[ ! -d $(SHAREDIR)/ ] ; then \
			mkdir $(SHAREDIR)/ ; \
	fi

xerces: dir
	@echo "Building Xerces-C"

clean:
	rf -rf $(SHAREDIR)