//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Utility.h"
#include "../src/Utility.h"

std::string UnitTestUtil::GetTestResoucreFolder()
{
    std::string sep = SystemUtil::GetSeparator();

    return std::string(GITPATH) + sep + "files";
}

