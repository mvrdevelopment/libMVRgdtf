//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

#include "IFolderIdentifier.h"


namespace VectorworksMVR
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		// {B4B088B1-3793-11DB-9C35-00508D5E9851}
		static const VWIID IID_FileIdentifier = { 0xB4B088B1, 0x3793, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };

		class DYNAMIC_ATTRIBUTE IFileIdentifier : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Set(const TXString& fullPath) = 0;
			virtual VCOMError VCOM_CALLTYPE	Set(EFolderSpecifier folderSpec, bool bUserFolder, const TXString& fileName) = 0;
			virtual VCOMError VCOM_CALLTYPE	Set(IFolderIdentifier* pFolderID, const TXString& fileName) = 0;
			virtual VCOMError VCOM_CALLTYPE	Clear() = 0;
			virtual VCOMError VCOM_CALLTYPE	IsSet() = 0;
			virtual VCOMError VCOM_CALLTYPE	ExistsOnDisk(bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFileFullPath(TXString& outPath) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFileName(TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetFileName(const TXString& name) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFileExtension(TXString& outExtension) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetFileExtension(const TXString& extension) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFileNameWithoutExtension(TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFolder(IFolderIdentifier** ppOutParentFolderID) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetAttributes(SAttributes& outAttributes) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetAttributes(const SAttributes& attributes) = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteOnDisk() = 0;
			virtual VCOMError VCOM_CALLTYPE	RenameOnDisk(const TXString& newName) = 0;
			virtual VCOMError VCOM_CALLTYPE DuplicateOnDisk(IFileIdentifier *pDestFileID, bool bOverwrite) = 0;
			virtual VCOMError VCOM_CALLTYPE LaunchInOS() = 0;
			virtual VCOMError VCOM_CALLTYPE RevealInOS() = 0;
			virtual VCOMError VCOM_CALLTYPE FormatFilename(TXString& formatName, Uint16 maxCharsWithoutSpace) = 0;
			virtual VCOMError VCOM_CALLTYPE	ValidateName(TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE GetAttributesTimeDateReference(EAttributesTimeReference ref, SAttributesDateTime& outData) = 0;
			virtual VCOMError VCOM_CALLTYPE SetAttributesTimeDateReference(EAttributesTimeReference ref, const SAttributesDateTime& data) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFileSize (size_t& outSize) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IFileIdentifier>			IFileIdentifierPtr;
		typedef std::vector<IFileIdentifierPtr>		TVWArray_IFileIdentifier;

		// ----------------------------------------------------------------------------------------------------
		// Errors from the filing routines
		const VCOMError		kVCOMError_BadPathSpecified		= 50;
		const VCOMError		kVCOMError_FileNotFound			= 51;
		const VCOMError		kVCOMError_AccessDenied			= 52;
		const VCOMError		kVCOMError_TooManyOpenFiles		= 54;
		const VCOMError		kVCOMError_DiskFull				= 55;
	}
}