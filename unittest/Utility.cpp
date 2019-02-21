//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Utility.h"

char UnitTestUtil::GetSysSeparator()
{
#ifdef _WINDOWS
    return '\\';
#else
    return '/';
#endif
}

