//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "Utility.h"
#include <string>

using VectorworksMVR::Filing::IFolderIdentifierPtr; 
using VectorworksMVR::Filing::IID_FolderIdentifier;

using namespace VectorworksMVR;

bool MvrUtil::isContainerType(ESceneObjType typ)
{
    bool res = (
       typ == ESceneObjType::Fixture
    || typ == ESceneObjType::FocusPoint
    || typ == ESceneObjType::Group
    || typ == ESceneObjType::Layer
    || typ == ESceneObjType::Projector
    || typ == ESceneObjType::SceneObj
    || typ == ESceneObjType::Truss
    || typ == ESceneObjType::VideoScreen
    || typ == ESceneObjType::Support);

    ASSERTN(kEveryone, res);

    return res;
}

/*static*/ void GdtfUtil::ConvertMatrix(const VectorworksMVR::STransformMatrix & smatrix, VWTransformMatrix & vwmatrix)
/* 
Converts a STransformMatrix to a VWTransformMatrix.
*/
{
    vwmatrix.fMatrix.mat[0][0] = smatrix.ux; vwmatrix.fMatrix.mat[0][1] = smatrix.uy; vwmatrix.fMatrix.mat[0][2] = smatrix.uz;
    vwmatrix.fMatrix.mat[1][0] = smatrix.vx; vwmatrix.fMatrix.mat[1][1] = smatrix.vy; vwmatrix.fMatrix.mat[1][2] = smatrix.vz;
    vwmatrix.fMatrix.mat[2][0] = smatrix.wx; vwmatrix.fMatrix.mat[2][1] = smatrix.wy; vwmatrix.fMatrix.mat[2][2] = smatrix.wz;
    vwmatrix.fMatrix.mat[3][0] = smatrix.ox; vwmatrix.fMatrix.mat[3][1] = smatrix.oy; vwmatrix.fMatrix.mat[3][2] = smatrix.oz;
}

/*static*/ void GdtfUtil::ConvertMatrix(const VWTransformMatrix & vwmatrix, VectorworksMVR::STransformMatrix & smatrix)
/*
Converts a VWTransformMatrix to a STransformMatrix.
*/
{
    smatrix.ux = vwmatrix.fMatrix.mat[0][0]; smatrix.uy = vwmatrix.fMatrix.mat[0][1]; smatrix.uz = vwmatrix.fMatrix.mat[0][2];
    smatrix.vx = vwmatrix.fMatrix.mat[1][0]; smatrix.vy = vwmatrix.fMatrix.mat[1][1]; smatrix.vz = vwmatrix.fMatrix.mat[1][2];
    smatrix.wx = vwmatrix.fMatrix.mat[2][0]; smatrix.wy = vwmatrix.fMatrix.mat[2][1]; smatrix.wz = vwmatrix.fMatrix.mat[2][2];
    smatrix.ox = vwmatrix.fMatrix.mat[3][0]; smatrix.oy = vwmatrix.fMatrix.mat[3][1]; smatrix.oz = vwmatrix.fMatrix.mat[3][2];
}

/*static*/ void GdtfUtil::ConvertVector3(const VWPoint3D & vector, VectorworksMVR::SVector3 & svector)
/*
Converts a VWPoint3D to a SVector3.
*/
{
    svector.x = vector.x;
    svector.y = vector.y;
    svector.z = vector.z;
}

TXString SystemUtil::ExtractFolderFromPath(TXString& path) 
/* 
   Deletes the folder part from the incoming string so that only the fileNam remains and returns it.    
*/
{
    TXString folder = "";    

    //-----------------------------------------------------------------------------
    ptrdiff_t pos = path.Find(kSeperator);

    while (pos > 0 )
	{
		// Copy string		
		for (ptrdiff_t i = 0; i <= pos; i++)	{ folder += path.GetAt(i); }		
		
		// Delete and find next
		path.Delete(0, pos + 1);
		pos = path.Find(kSeperator);
	}	

    return folder;
}

