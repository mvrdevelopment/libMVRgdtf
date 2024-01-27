//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "XmlFileHelper.h"

using namespace VectorworksMVR::Filing;

namespace VectorworksMVR
{
	class HashManager
	{
	public:
		
		static bool CheckHashForFile(const IFileIdentifierPtr& fileToHash, const IFileIdentifierPtr& hashsumFile );
        static bool CreateHashForBuffer(SceneData::ISceneDataZipBuffer& bufferToHash, SceneData::ISceneDataZipBuffer& hashFileBuffer);
		static bool CreateHashForFile(const IFileIdentifierPtr& fileToHash, SceneData::ISceneDataZipBuffer& outHashsumFile );
        static bool CheckHashForBuffer(SceneData::ISceneDataZipBuffer& fileToHash, SceneData::ISceneDataZipBuffer& hashsumFile);
		
	private:
		static bool CreateHash(const IFileIdentifierPtr& fileToHash, TXString& outHash);
        static bool CreateHash(SceneData::ISceneDataZipBuffer& bufferToHash, TXString& outHash);
	};
}
