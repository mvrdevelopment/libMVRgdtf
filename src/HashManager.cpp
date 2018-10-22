//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "HashManager.h"
#include "sha256/sha256.h"
#include "GDTFManager.h"
#include "XmlFileHelper.h"

bool HashManager::HashManager::CreateHashForFile(const IFileIdentifierPtr& fileToHash, SceneData::ISceneDataZipBuffer& outHashsumFile)
{


	TXString hash;
	if (CreateHash(fileToHash, hash))
	{
		outHashsumFile.SetData((void*) hash.GetCharPtr(), hash.GetLength());
		return true;
	}
	
	return false;
}

bool HashManager::HashManager::CreateHashForBuffer(SceneData::ISceneDataZipBuffer &bufferToHash, SceneData::ISceneDataZipBuffer &hashFileBuffer)
{
    TXString hash;
    if(CreateHash(bufferToHash, hash))
    {
        size_t length		= hash.GetLength();
        void* data			= malloc(length * sizeof(char));
        const char* hashHar = hash.GetCharPtr();
        
        memcpy(data, hashHar, length);
		
		// Set Hash File
		hashFileBuffer.SetData(data, length);
		
		// Housekeeping
		std::free(data);
		
		return true;
    }
    
    
    return false;
}

bool HashManager::HashManager::CheckHashForFile(const IFileIdentifierPtr& fileToHash, const IFileIdentifierPtr& hashsumFile)
{
	//--------------------------------------------------------------------------------
	// Generate the hash for the file
	TXString hash;
	if ( CreateHash(fileToHash, hash) )
	{
		TXString storedHash;
		
		//--------------------------------------------------------------------------------
		// Read the hash file
		IRawOSFilePtr rawFile (IID_RawOSFile);
		if (VCOM_SUCCEEDED(rawFile->Open(hashsumFile, true, false, false, false)))
		{
			Uint64 length = 0;
			
			if (VCOM_SUCCEEDED(rawFile->GetFileSize(length)))
			{
				// Create buffer
				void* buffer = malloc (sizeof(char) * length);
				
				if (VCOM_SUCCEEDED(rawFile->Read(0, length, buffer)))
				{
					// Read file
					storedHash = TXString((char*)buffer, length);
					
					ASSERTN(kEveryone, hash.IsEmpty() == false);
					ASSERTN(kEveryone, storedHash.IsEmpty() == false);
					if (hash == storedHash) { return true; }
				}
				
				// Housekeeping
				std::free(buffer);
			}
		}
	}
	
	return false;
}

bool HashManager::HashManager::CreateHash(const IFileIdentifierPtr& fileToHash, TXString& outHash)
{
	//-------------------------------------------------------------------------------------------------
	// Check if there is a pointer
	ASSERTN(kEveryone, fileToHash != nullptr);
	if (fileToHash == nullptr) { return false; }
	
	//-------------------------------------------------------------------------------------------------
	// Check if there a file
	bool existsOnDisk = false;
	fileToHash->ExistsOnDisk(existsOnDisk);
	ASSERTN(kEveryone, existsOnDisk);
	if (existsOnDisk == false) { return false; }
	
	
	//-------------------------------------------------------------------------------------------------
	// Do the magic
	IRawOSFilePtr file (IID_RawOSFile);
	
	if (VCOM_SUCCEEDED(file->Open(fileToHash, true, false, false, false)))
	{
		Uint64 length = 0;
		if(VCOM_SUCCEEDED(file->GetFileSize(length)))
		{
			void* buffer = malloc(sizeof(char) * length);
			
			if(VCOM_SUCCEEDED(file->Read(0, length, buffer)))
			{
				SHA256 hashObj;
				hashObj.add(buffer, length);
				
				TXString hash = hashObj.getHash();
				
				outHash = hash;
				return true;
				
			}
			
			// Housekeeping
			std::free(buffer);
		}
	}
	
	return false;
}

bool HashManager::HashManager::CreateHash(SceneData::ISceneDataZipBuffer& bufferToHash, TXString& outHash)
{
	// Prepare Storage
    size_t  bufferSize	= 0;
    void*   ptr			= nullptr;
	
    if(VCOM_SUCCEEDED(bufferToHash.GetDataSize(bufferSize)) && VCOM_SUCCEEDED(bufferToHash.GetData(ptr)))
	{
		// Create the hash
        SHA256 hashObj;
        hashObj.add(ptr, bufferSize);
		
		// Store the hash
        TXString hash	= hashObj.getHash();
        outHash			= hash;
        return true;
    }
    return false;
}

bool HashManager::HashManager::CheckHashForBuffer(SceneData::ISceneDataZipBuffer& bufferToHash, SceneData::ISceneDataZipBuffer& hashsumFile)
{
    TXString bufferHash;
    if(::HashManager::HashManager::CreateHash(bufferToHash, bufferHash))
    {
		
        void*		ptr			= nullptr;
        size_t		length		= 0;
        if(VCOM_SUCCEEDED(hashsumFile.GetData(ptr))&&VCOM_SUCCEEDED(hashsumFile.GetDataSize(length)))
		{
			// Create the hash string
            TXString storedHash ((char*)ptr, length);
			
			// Check if they are the sameb
            if(storedHash == bufferHash){ return true; }
        }
    }
    return false;
}
