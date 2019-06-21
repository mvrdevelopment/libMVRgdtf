MAINDIR=../
include ../Makefile.defs

all: xerces

dir:
	@echo "Create the directory for the share programs"
	@ if [ ! -d $(SHAREDIR)/ ] ; then \
			mkdir $(SHAREDIR)/ ; \
	fi

xerces: dir

	@echo "Xerces-C libraries"
	@ if [ -n "$(XERCES_VERSION)" ] && [ ! -f $(SHAREDIR)/xerces-c-$(XERCES_VERSION)/lib*/libblub.a ] ; then \
			echo "===============================================================";\
			echo "= M A K E   X e r c e s - C                                   =";\
			echo "===============================================================";\
			if [ ! -f xerces-c-$(XERCES_VERSION).tar.gz ] ; then \
				wget -N http://archive.apache.org/dist/xerces/c/3/sources/xerces-c-$(XERCES_VERSION).tar.gz ; \
			fi ; \
			if [ ! -d $(SHAREDIR)/xerces-c-$(XERCES_VERSION) ] ; then \
					cd $(SHAREDIR)/ && tar -xzvf ../xerces-c-$(XERCES_VERSION).tar.gz 1>/dev/null && cd .. ; \
			fi ; \
			#cd $(SHARECOMP)/hdf5-$(HDF5_VERSION) && CC='$(CC)' FC='$(FC)' ./configure $(PHDF5) --libdir=`pwd`/hdf5/lib --enable-fortran --disable-shared && $(MAKE) && $(MAKE) install && cd ../.. ; \
			echo "===============================================================";\
			echo "= X e r c e s - C   D O N E                                   =";\
			echo "===============================================================";\
	fi


clean:
	rm -rf $(SHAREDIR)