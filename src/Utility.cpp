//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "Utility.h"
#include <string>

using VectorWorks::Filing::IFolderIdentifierPtr; 
using VectorWorks::Filing::IID_FolderIdentifier;


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

bool SystemUtil::CreateFolderDefinitlyOnDisk(const TXString& folderPath)
{
    IFolderIdentifierPtr folder = (IID_FolderIdentifier);
    folder->Set(folderPath);
    
    bool exists;  folder->ExistsOnDisk(exists);
    
    if (exists) 
    {
        // Nothing to to do!
        return true;
    }

    // Try to create the Folder; This only works when all the ParentFolder exists.
    folder->CreateOnDisk();

    // Check if this was succesfull
    folder->ExistsOnDisk(exists);

    if (! exists) 
    {
        ptrdiff_t pos = folderPath.ReverseFind( kSeperator );

        if (pos > 0)
        {
            TXString parentFolder = folderPath.Left(pos);
            
            if ( ! parentFolder.IsEmpty()) 
            {
                // Try to create the Parent folder; Remove the last folder from the path if possible.
                SystemUtil::CreateFolderDefinitlyOnDisk(parentFolder);
            }
            else 
            {
                return false;
            }
        }
        else 
        {
            // Could not find a seperator in the folder path. This should not happen.
            DSTOP((kEveryone, "Could not find a seperator in the folder path."));
            return false;
        }
    }
    else 
    {
        return true;
    }

    // Now all the Parentfolders should  and we can try to create the top folder again:
    folder->CreateOnDisk();
    folder->ExistsOnDisk(exists);
    
    return exists;
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

