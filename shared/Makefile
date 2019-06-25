include ../Makefile.defs

all: xerces

dir:
	@echo "Create the directory for the share programs"
	@ if [ ! -d $(SHAREDBUILDSDIR)/ ] ; then \
			mkdir $(SHAREDBUILDSDIR)/ ; \
			mkdir $(SHAREDLIBDIR)/ ; \
			mkdir $(SHAREDINCDIR)/ ; \
			mkdir $(SHAREDBINDIR)/ ; \
	fi

xerces: dir

	@# "Xerces-C libraries"
	@ if [ -n "$(XERCES_VERSION)" ] && [ ! -f $(SHAREDLIBDIR)/libxerces-c.a ] ; then \
			echo "===============================================================";\
			echo "= M A K E   X e r c e s - C                                   =";\
			echo "===============================================================";\
			if [ ! -f xerces-c-$(XERCES_VERSION).zip ] ; then \
				wget -N http://archive.apache.org/dist/xerces/c/3/sources/xerces-c-$(XERCES_VERSION).zip ; \
			fi ; \
			if [ ! -d $(SHAREDBUILDSDIR)/xerces-c-$(XERCES_VERSION) ] ; then \
					cd $(SHAREDBUILDSDIR)/ && unzip ../xerces-c-$(XERCES_VERSION).zip 1>/dev/null && cd .. ; \
			fi ; \
			cd $(SHAREDBUILDSDIR)/xerces-c-$(XERCES_VERSION) && ./configure $(XERCES_CONFIGURE_OPTIONS) && $(MAKE) && $(MAKE) install && cd ../.. ; \
			echo "===============================================================";\
			echo "= X e r c e s - C   D O N E                                   =";\
			echo "===============================================================";\
	fi

clean:
	rm -rf $(SHAREDBUILDSDIR) && rm -rf $(SHAREDLIBDIR) && rm -rf $(SHAREDINCDIR) && rm -rf $(SHAREDBINDIR)
