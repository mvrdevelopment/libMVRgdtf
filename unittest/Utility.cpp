//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Utility.h"

std::string UnitTestUtil::GetSysSeparator()
{
#ifdef _WINDOWS
    return "\\";
#else
    return "/";
#endif
}

