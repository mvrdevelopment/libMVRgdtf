//
// Copyright (c) Diehl Graphsoft, Inc. 2006.
// All Rights Reserved.
// 

#pragma once

#include "Prefix/StdAfx.h"
#include "FolderIdentifier.h"


namespace VectorworksMVR
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		class CFileIdentifier : public VCOMImpl<IFileIdentifier>
		{
		public:
									CFileIdentifier();
			virtual					~CFileIdentifier();

			TXString				GetFileFullPath() const;
			VCOMError				SetFileFullPath(const TXString& fileFullName);

		// IFileIdentifier
		public:
			virtual VCOMError	VCOM_CALLTYPE	Set(const TXString& fullPath);
			virtual VCOMError	VCOM_CALLTYPE	Set(EFolderSpecifier folderSpec, bool bUserFolder, const TXString& fileName);
			virtual VCOMError	VCOM_CALLTYPE	Set(IFolderIdentifier* pFolderID, const TXString& fileName);
			virtual VCOMError	VCOM_CALLTYPE	Clear();
			virtual VCOMError	VCOM_CALLTYPE	IsSet();
			virtual VCOMError	VCOM_CALLTYPE	ExistsOnDisk(bool& outValue);
			virtual VCOMError	VCOM_CALLTYPE	GetFileFullPath(TXString& outPath);
			virtual VCOMError	VCOM_CALLTYPE	GetFileName(TXString& outName);
			virtual VCOMError	VCOM_CALLTYPE	SetFileName(const TXString& name);
			virtual VCOMError	VCOM_CALLTYPE	GetFileExtension(TXString& outExtension);
			virtual VCOMError	VCOM_CALLTYPE	SetFileExtension(const TXString& extension);
			virtual VCOMError	VCOM_CALLTYPE	GetFileNameWithoutExtension(TXString& outName);
			virtual VCOMError	VCOM_CALLTYPE	GetFolder(IFolderIdentifier** ppOutParentFolderID);
			virtual VCOMError	VCOM_CALLTYPE	GetAttributes(SAttributes& outAttributes);
			virtual VCOMError	VCOM_CALLTYPE	SetAttributes(const SAttributes& attributes);
			virtual VCOMError	VCOM_CALLTYPE	DeleteOnDisk();
			virtual VCOMError	VCOM_CALLTYPE	RenameOnDisk(const TXString& newName);
			virtual VCOMError	VCOM_CALLTYPE	DuplicateOnDisk(IFileIdentifier *pDestFileID, bool bOverwrite);
			virtual VCOMError	VCOM_CALLTYPE	LaunchInOS();
			virtual VCOMError	VCOM_CALLTYPE	RevealInOS();
			virtual VCOMError	VCOM_CALLTYPE	FormatFilename(TXString& formatName, Uint16 maxCharsWithoutSpace);
			virtual VCOMError	VCOM_CALLTYPE	ValidateName(TXString& outName);
			virtual VCOMError	VCOM_CALLTYPE	GetAttributesTimeDateReference(EAttributesTimeReference ref, SAttributesDateTime& outData);
			virtual VCOMError	VCOM_CALLTYPE	SetAttributesTimeDateReference(EAttributesTimeReference ref, const SAttributesDateTime& data);
			virtual VCOMError	VCOM_CALLTYPE	GetFileSize (size_t& outSize);

		// Tools
		public:
			static void			ValidateFilename(TXString& outName);
			static void			ConvertFilename(TXString& outName);

		private:
			CFolderIdentifier	fFolderID;
			TXString			fFileName;
		};
	}
}