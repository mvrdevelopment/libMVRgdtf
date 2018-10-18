//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		struct SAttributes
		{
			bool	fbReadOnly;
			bool	fbHidden;
			bool	fbSystem;
			bool	fbTemporary;
			bool	fbEncrypted;
			bool	fbArchive;
			bool	fbDirectory;
			bool	fbCanRead;
			bool	fbCanWrite;
			bool	fbCanExecute;
			bool	fbCanBrowse;
		};

		// ----------------------------------------------------------------------------------------------------
		struct SAttributesDateTime
		{
			Uint32	fYear;
			Uint32	fMonth;
			Uint32	fDay;
			Uint32	fHour;
			Uint32	fMinute;
			Uint32	fSecond;
		};

		enum EAttributesTimeReference
		{
			eAttributesTimeReference_Created,
			eAttributesTimeReference_LastAccessed,
			eAttributesTimeReference_LastWritten,
			eAttributesTimeReference_LastBackup
		};

		// ----------------------------------------------------------------------------------------------------
		enum EFolderContentListenerResult
		{
			eFolderContentListenerResult_Continue,
			eFolderContentListenerResult_StopNoError,
			eFolderContentListenerResult_StopError,
		};

		// ----------------------------------------------------------------------------------------------------
		class IFolderIdentifier;
		class IFileIdentifier;

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IFolderContentListener
		{
		public:
			virtual												~IFolderContentListener()		{}

			virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFolderContent(IFolderIdentifier* pFolderID) = 0;
			virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFileContent(IFileIdentifier* pFileID) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef std::function<EFolderContentListenerResult(IFolderIdentifier* folderID)>	TFolderContentCallback_Folder;
		typedef std::function<EFolderContentListenerResult(IFileIdentifier* fileID)>		TFolderContentCallback_File;

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IWorkspaceFileInfoListener
		{
		public:
			virtual												~IWorkspaceFileInfoListener()		{}

			virtual EFolderContentListenerResult VCOM_CALLTYPE	OnWorkspaceFileInfo(const char* fullPath, const char* fileName, short workspaceType) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {C06DFE83-3791-11DB-9C35-00508D5E9851}
		static const VWIID IID_FolderIdentifier = { 0xC06DFE83, 0x3791, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };

		class DYNAMIC_ATTRIBUTE IFolderIdentifier : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Set(const TXString& fullPath) = 0;
			virtual VCOMError VCOM_CALLTYPE	Set(EFolderSpecifier folderSpec, bool bUserFolder) = 0;
			virtual VCOMError VCOM_CALLTYPE	Set(EFolderSpecifier folderSpec, bool bUserFolder, const TXString& subFolderName) = 0;
			virtual VCOMError VCOM_CALLTYPE	Set(IFolderIdentifier* pParentFolder, const TXString& folderName) = 0;
			virtual VCOMError VCOM_CALLTYPE	Clear() = 0;
			virtual VCOMError VCOM_CALLTYPE	IsSet() = 0;
			virtual VCOMError VCOM_CALLTYPE	ExistsOnDisk(bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFullPath(TXString& outPath) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetName(TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetParentFolder(IFolderIdentifier** ppOutParentFolderID) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetAttributes(SAttributes& outAttributes) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetAttributes(const SAttributes& attributes) = 0;
			virtual VCOMError VCOM_CALLTYPE	EnumerateContents(IFolderContentListener* pListener, bool bReqursive) = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateOnDisk() = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteOnDisk() = 0;
			virtual VCOMError VCOM_CALLTYPE RevealInOS() = 0;
			virtual VCOMError VCOM_CALLTYPE DuplicateOnDisk(IFolderIdentifier * newFolder, bool overrideIfNecessary = false, TXString* displayProgressDialog = NULL) = 0;
			virtual VCOMError VCOM_CALLTYPE FormatFoldername(TXString& formatName, Uint16 maxCharsWithoutSpace) = 0;
			virtual VCOMError VCOM_CALLTYPE	ValidateName(TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE GetAttributesTimeDateReference(EAttributesTimeReference ref, SAttributesDateTime& outData) = 0;
			virtual VCOMError VCOM_CALLTYPE SetAttributesTimeDateReference(EAttributesTimeReference ref, const SAttributesDateTime& data) = 0;

		// VW2016
		public:
			virtual VCOMError VCOM_CALLTYPE	EnumerateContents(TFolderContentCallback_Folder folderCallback, TFolderContentCallback_File fileCallback, bool bReqursive) = 0; // use nullptr if callbacks not defined
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IFolderIdentifier>		IFolderIdentifierPtr;
	}
}