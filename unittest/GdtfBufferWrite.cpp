//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfBufferWrite.h"
#include <iostream>
#include "Utility.h"
#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;

#include <cstdio>

#ifdef GS_LIN
#include <unistd.h>
#include <stdio.h>
#endif


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)


GdtfBufferWrite::GdtfBufferWrite(const std::string& currentDir)
{
	fBufferLength 	= 0;
	fBuffer 		= nullptr;
	fFileBuffer 	= nullptr;
}

GdtfBufferWrite::~GdtfBufferWrite()
{
	delete[] fBuffer;
	delete[] fFileBuffer;
}

bool GdtfBufferWrite::ExecuteTest()
{
	std::cout << "=                                        GdtfBufferWrite                                      =" << std::endl;

	Write();
	Read();

	return true;
}

void GdtfBufferWrite::Write()
{
	IGdtfFixturePtr gdtfFixture (IID_IGdtfFixture);
	MvrUUID uuid (225204211, 177198167, 1575790, 96627);
    if(__checkVCOM(gdtfFixture->OpenForWrite("My FixtureName","My Manufacturer", uuid)))
    {
    	gdtfFixture->SetShortName("Short Name");

		fFileBuffer = new char[2048];

		gdtfFixture->AddBufferToGdtfFile("test.png", fFileBuffer, 2048, ERessourceType::RessoureFixture);
		gdtfFixture->SetFixtureThumbnail("test.png");
	
		gdtfFixture->Close();

		__checkVCOM(gdtfFixture->GetBufferLength(fBufferLength));

		fBuffer = new char[fBufferLength];
		__checkVCOM(gdtfFixture->ToBuffer(fBuffer));

    }
}

void GdtfBufferWrite::Read()
{
	IGdtfFixturePtr gdtfFixture (IID_IGdtfFixture);
	if(__checkVCOM(gdtfFixture->FromBuffer(fBuffer, fBufferLength)))
	{
		this->checkifEqual("GetShortName "				, gdtfFixture->GetShortName()			, "Short Name");
		this->checkifEqual("GetFixtureThumbnail "	    , gdtfFixture->GetFixtureThumbnail()	, "test.png");

	}
}
