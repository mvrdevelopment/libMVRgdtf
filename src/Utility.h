//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

class GdtfUtil
{   
public:
    static void ConvertMatrix (const VectorworksMVR::STransformMatrix & smatrix, VWTransformMatrix & vwmatrix);
    static void ConvertMatrix (const VWTransformMatrix & vwmatrix, VectorworksMVR::STransformMatrix & smatrix);
};

class SystemUtil
{
public:
    static std::string GetSeparator();
    static bool CreateFolderDefinitlyOnDisk(const TXString& folderPath);
    static TXString ExtractFolderFromPath(TXString & path);
};
