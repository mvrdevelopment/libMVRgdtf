//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "GetCountOfChannels.h"

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfGetCountOfLinkedChannelsForGeometry::GdtfGetCountOfLinkedChannelsForGeometry(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

GdtfGetCountOfLinkedChannelsForGeometry::~GdtfGetCountOfLinkedChannelsForGeometry()
{  
}


std::string GdtfGetCountOfLinkedChannelsForGeometry::GetUnitTestName()
{  
    return  std::string("GdtfGetCountOfLinkedChannelsForGeometry");
}

void GdtfGetCountOfLinkedChannelsForGeometry::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  

}

void GdtfGetCountOfLinkedChannelsForGeometry::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  


}
