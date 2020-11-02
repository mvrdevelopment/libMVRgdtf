//
// Copyright (c) Diehl Graphsoft, Inc. 2006.
// All Rights Reserved.
// 

#pragma once

namespace VectorworksMVR
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		class CFolderIdentifier : public VCOMImpl<IFolderIdentifier>
		{
		public:
										CFolderIdentifier();
			virtual						~CFolderIdentifier();

			VCOMError					SetFullPath(const TXString& fullPath);
			TXString					GetFullPath() const;

		// tools
		public:
			static EFolderSpecifier		TranslateFolderSpec(EFolderSpecifier folderSpec);

		// IFolderIdentifier
		public:
			virtual VCOMError	VCOM_CALLTYPE	Set(const TXString& fullPath);
			virtual VCOMError	VCOM_CALLTYPE	Set(EFolderSpecifier folderSpec, bool bUserFolder);
			virtual VCOMError	VCOM_CALLTYPE	Set(EFolderSpecifier folderSpec, bool bUserFolder, const TXString& subFolderName);
			virtual VCOMError	VCOM_CALLTYPE	Set(IFolderIdentifier* pParentFolder, const TXString& folderName);
			virtual VCOMError	VCOM_CALLTYPE	Clear();
			virtual VCOMError	VCOM_CALLTYPE	IsSet();
			virtual VCOMError	VCOM_CALLTYPE	ExistsOnDisk(bool& outValue);
			virtual VCOMError	VCOM_CALLTYPE	GetFullPath(TXString& outPath);
			virtual VCOMError	VCOM_CALLTYPE	GetName(TXString& outName);
			virtual VCOMError	VCOM_CALLTYPE	GetParentFolder(IFolderIdentifier** ppOutParentFolderID);
			virtual VCOMError	VCOM_CALLTYPE	GetAttributes(SAttributes& outAttributes);
			virtual VCOMError	VCOM_CALLTYPE	SetAttributes(const SAttributes& attributes);
			virtual VCOMError	VCOM_CALLTYPE	EnumerateContents(IFolderContentListener* pListener, bool bReqursive);
			virtual VCOMError	VCOM_CALLTYPE	CreateOnDisk();
			virtual VCOMError	VCOM_CALLTYPE	DeleteOnDisk();
			virtual VCOMError	VCOM_CALLTYPE	RevealInOS();
			virtual VCOMError	VCOM_CALLTYPE	DuplicateOnDisk(IFolderIdentifier * newFolder, bool overrideIfNecessary = false, TXString* displayProgressDialog = NULL);
			virtual VCOMError	VCOM_CALLTYPE	FormatFoldername(TXString& formatName, Uint16 maxCharsWithoutSpace);
			virtual VCOMError	VCOM_CALLTYPE	ValidateName(TXString& outName);
			virtual VCOMError	VCOM_CALLTYPE	GetAttributesTimeDateReference(EAttributesTimeReference ref, SAttributesDateTime& outData);
			virtual VCOMError	VCOM_CALLTYPE	SetAttributesTimeDateReference(EAttributesTimeReference ref, const SAttributesDateTime& data);

			virtual VCOMError	VCOM_CALLTYPE	EnumerateContents(TFolderContentCallback_Folder folderCallback, TFolderContentCallback_File fileCallback, bool bReqursive);

		// Tools
		public:
			static void			ValidateFoldername(TXString& outName);
			static void			ConvertFoldername(TXString& outName);

		private:
			bool				EnumerateContentsHandler(IFolderContentListener* pListener, const CFolderIdentifier& folder, bool bReqursive, VCOMError& outError);
			
		private:
			// this actually keep the full path
			// this is done like this (and not just TFolderIdentifier)
			// because TFolderIdentifier::SetByFullPath on mac requeres the path to exist
			TXStringArray		farrFolderHierarchy;

		};
	}
}
