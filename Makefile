#################################################################
#																#
#	Makefile for libVectorworksMvrGdtf							#
#																#
#################################################################

# set library name
targetLibName	= libVectorworksMvrGdtf

# Folders
buildFolder = C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf

#-------------------------------------------------------------------------------------------------------------------------------
# set platform compiler and linker flags

# Windows
ifeq ($(OS),Windows_NT)
		CXX			= cl.exe			#c++ compiler
#		CXXFLAGS	= /D_USRDLL /D_WINDLL /P
		CXXFLAGS	= /JMC /permissive- /GS /analyze- /W3 /Zc:wchar_t /ZI /Gm- /Od /sdl /Fd"Debug\vc141.pdb" /Zc:inline /fp:precise /D "WIN32" /D "_DEBUG" /D "LIBVECTORWORKSMVRGDTF_EXPORTS" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd /FC /Fa"Debug\" /EHsc /nologo /Fo"Debug\" /Fp"Debug\libVectorworksMvrGdtf.pch" /diagnostics:classic 
		CXXFLAGS	+= /DGS_WIN=1		
		LD			= link.exe				# linker
		LDFLAGS		= /OUT:"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf\libVectorworksMvrGdtf.dll" /MANIFEST /NXCOMPAT /PDB:"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf\libVectorworksMvrGdtf.pdb" /DYNAMICBASE "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /IMPLIB:""C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf\libVectorworksMvrGdtf.lib" /DEBUG /DLL /MACHINE:X86 /INCREMENTAL /PGD:"C:\Users\admin\Documents\DEV\libVectorworksMvrGdtf\libVectorworksMvrGdtf.pgd" /SUBSYSTEM:WINDOWS /MANIFESTUAC:"level='asInvoker' uiAccess='false'" /ManifestFile:"Debug\libVectorworksMvrGdtf.dll.intermediate.manifest" /ERRORREPORT:PROMPT /NOLOGO /TLBID:1 
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
OBJECTS = $(SOURCES:.cpp=.o)


#-------------------------------------------------------------------------------------------------------------------------------
# Make Targets
targetLib = $(targetLibName)$(libExt)

# ALL
all: $(targetLib)

# Build targetLib
# Windows

$(targetLibName).dll: $(SOURCES)
	@echo Start to build lib on Win
	$(CXX) $(CXXFLAGS) src\GSString.cpp $(LDFLAGS)


# Mac Linux
$(targetLibName).so: $(OBJECTS)
	@echo $(targetLibName)
	$(CXX) $(CXXFLAGS) -c -MMD -MP $(LDFLAGS) -o $(targetLib) $(OBJECTS)