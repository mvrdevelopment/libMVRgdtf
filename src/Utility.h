//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#ifdef _WINDOWS
#define kSeperator '\\'
#else
#define kSeperator '/'
#endif

namespace VectorworksMVR
{
	class GdtfUtil
	{
	public:
		static void ConvertMatrix(const VectorworksMVR::STransformMatrix & smatrix, VWTransformMatrix & vwmatrix);
		static void ConvertMatrix(const VWTransformMatrix & vwmatrix, VectorworksMVR::STransformMatrix & smatrix);
	};

	class SystemUtil
	{
	public:
		static TXString ExtractFolderFromPath(TXString & path);
	};
}