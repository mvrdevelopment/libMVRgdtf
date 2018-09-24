#################################################################
#																#
#	Makefile for libVectorworksMvrGdtf							#
#																#
#################################################################

# set library name
targetLibName	= libVectorworksMvrGdtf

#-------------------------------------------------------------------------------------------------------------------------------
# set platform compiler and linker flags

# Windows
ifeq ($(OS),Windows_NT)
		CXX			= cl.exe			#c++ compiler
		CXXFLAGS	= /RTCc /Yu"StdAfx.h" /MP /FR"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf" \
						/GS /W3 /Gy /Zc:wchar_t /Zi /Gm/ /Od /Zc:inline /fp:precise /errorReport:prompt \
						/GF/ /WX /Zc:forScope /RTC1 /GR /Gd /MDd /FC \
						/Fa"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf" \
						/EHsc /nologo /Fo"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf" \
						/Fp"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf" \
						/diagnostics:classic
		CXXFLAGS	+= /DGS_WIN=1		
		LD			= link.exe				# linker
		LDFLAGS		= /OUT:"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf.dll" /MANIFEST /NXCOMPAT \
						/PDB:"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf.pdb" \
						/LARGEADDRESSAWARE \
						/IMPLIB:"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf.lib" /DEBUG /DLL /MACHINE:X64 \
						/NODEFAULTLIB:"libc" /SAFESEH:NO /INCREMENTAL \
						/PGD:"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf.pgd" /SUBSYSTEM:WINDOWS \
						/MANIFESTUAC:"level='asInvoker' uiAccess='false'" \
						/ManifestFile:"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf.dll.intermediate.manifest" \
						/ERRORREPORT:PROMPT /NOLOGO \
						/LIBPATH:"C:\Users\admin\Documents\DEV\VectorworksGDTFExchange-VW23.0.x\AppSource\Source\Plug-Ins\DeerSoft\VectorworksMVR\..\..\..\..\Output\LibWin\Debug" \
						/LIBPATH:"C:\Users\admin\Documents\DEV\VectorworksGDTFExchange-VW23.0.x\AppSource\Source\Plug-Ins\DeerSoft\VectorworksMVR\..\..\..\..\Output\SDK\Debug" \
						/LIBPATH:"C:\Users\admin\Documents\DEV\VectorworksGDTFExchange-VW23.0.x\AppSource\Source\Plug-Ins\DeerSoft\VectorworksMVR\..\..\..\..\Output\LibWinThirdParty\Debug" \
						/LIBPATH:"C:\Users\admin\Documents\DEV\VectorworksGDTFExchange-VW23.0.x\AppSource\Source\Plug-Ins\DeerSoft\VectorworksMVR\..\..\..\..\Output\LibWinThirdParty" \
						/TLBID:1 
		libExt		= .dll

else
    UNAME_S := $(shell uname -s)

# Linux
    ifeq ($(UNAME_S),Linux)
        CXX			= g++				#c++ compiler and linker(gcc or ld)
		CXXFLAGS	= -g -std=c++11		#c++ compiler flags
		CXXFLAGS	+= -DGS_LIN=1
		LDFLAGS		= -shared -DfPIC	#linker flags
		libExt		= .so
    endif

# Mac
    ifeq ($(UNAME_S),Darwin)
		CXX			= g++				#c++ compiler and linker(gcc or ld)
		CXXFLAGS	= -g -std=c++11		#c++ compiler flags
		CXXFLAGS	+= -DGS_MAC=1
		LDFLAGS		= -shared -DfPIC	#linker flags
		libExt		= .so
    endif
endif

#-------------------------------------------------------------------------------------------------------------------------------
# What to compile
SOURCES = $(shell echo src/*.cpp)
HEADERS = $(shell echo src/*.h)
OBJECTS = $(SOURCES:.c=.o)


#-------------------------------------------------------------------------------------------------------------------------------
# Make Targets

#----------------------------
# Testing
$(info $(OS))
$(info $(UNAME_S))
$(info $(targetLibName))
#----------------------------

# ALL
all: $(targetLibName)$(libExt)

# Build targetLib
# Windows
$(targetLibName).dll: $(OBJECTS)
	@echo $(targetLibName)
	$(CXX) $(CXXFLAGS)
	$(LD) $(LDFLAGS) $(OBJECTS)

# Mac Linux
$(targetLibName).so: $(OBJECTS)
	@echo $(targetLibName)
	$(CXX) $(CXXFLAGS) -c -MMD -MP $(LDFLAGS) -o $(targetLib) $(OBJECTS)