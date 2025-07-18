//-----------------------------------------------------------------------------
//----- Copyright MVR Group
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
		static void ConvertVector3(const VWPoint3D & vector, VectorworksMVR::SVector3 & svector);

		static bool IsValidNameChar( TXChar codepoint );
		static void DoesNameContainInvalidChars( TXString& name );
	};

    class MvrUtil
    {
    public:
        static bool isContainerType(ESceneObjType typ);
    };

	class SystemUtil
	{
	public:
		static TXString ExtractFolderFromPath(TXString & path);
	};
}