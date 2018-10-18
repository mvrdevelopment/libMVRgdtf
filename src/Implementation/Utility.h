//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "StdAfx.h"
#include "VectorworksMVR.h"

class Utility
{   
public:
    static void ConvertMatrix (const VectorworksMVR::STransformMatrix & smatrix, VWTransformMatrix & vwmatrix);
    static void ConvertMatrix (const VWTransformMatrix & vwmatrix, VectorworksMVR::STransformMatrix & smatrix);
};
