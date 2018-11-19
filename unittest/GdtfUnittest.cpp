//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfUnittest.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;

#define __checkVCOM(x) this->checkVCOM(x, #x)

GdtfUnittest::GdtfUnittest(const std::string& currentDir)
{
    fPath = currentDir;
    fPath += std::string("/testGdtf.gdtf");

    std::cout << "Export File to" << fPath << std::endl; 
}

GdtfUnittest::~GdtfUnittest()
{
    
}

bool GdtfUnittest::ExecuteTest()
{
	std::cout << "=                    GdtfUnittest                    =" << std::endl;
    WriteFile();
    ReadFile();

    return true;
}

void GdtfUnittest::WriteFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
	IGdtfFixturePtr gdtfWrite (IID_IGdtfFixture);

    MvrUUID uuid (1,2,3,4);
    if(__checkVCOM(gdtfWrite->OpenForWrite(fPath.c_str(),"FixtureName","Manufacturer", uuid)))
    {



        __checkVCOM(gdtfWrite->Close());
    }
}

void GdtfUnittest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
    IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);

    
    if(__checkVCOM(gdtfRead->ReadFromFile(fPath.c_str())))
    {
        // Check Fixture Name
        MvrString fixtureName = gdtfRead->GetName();
        this->checkifEqual("GetName", fixtureName, "FixtureName");
        
    }

	
}