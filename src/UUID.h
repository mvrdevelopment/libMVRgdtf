//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Tools
	{
		// NOTE! You have to import library 'Rpcrt4.lib' on windows
		// for this class to be used !!!
		class UUID
		{
		public:
						UUID();
						// the bits are reversed
						//	for example:
						//	{09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
						//	'975DE909' 'd5434C36' '4CFFDF8A' 'A741ECE0'
						UUID(Uint32 a, Uint32 b, Uint32 c, Uint32 d);
						// copy the bytes one by one
						UUID(const Uint8* const pArray, size_t size);
						UUID(const VWIID& iid);
						UUID(const UUID& src);
						// Trows exception if not in this format
						// {09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
						UUID(const TXString& str);
						~UUID();

			UUID&		operator=(const UUID& src);

			bool		operator==(const UUID& id) const;
			bool		operator!=(const UUID& id) const;
						operator TXString() const;

			// create four 32 Bit integer from the components of the GUID structure
			// the bits are reversed
			//	for example:
			//	{09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
			//	'975DE909' 'd5434C36' '4CFFDF8A' 'A741ECE0'
			void		GetUUID(Uint32& out1, Uint32& out2, Uint32& out3, Uint32& out4) const;
			// copy the byes one by one as they are
			void		GetUUID(Uint8* pArray, size_t size) const;
			// get as VCOM IID
			void		GetUUID(VWIID& out) const;

			TXString	ToString(bool includeBrackets) const;

			TXString	Encode(const TXString& arrChars) const;

		protected:
			// {09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
			Uint8		fData[16];
		};
	}
}
