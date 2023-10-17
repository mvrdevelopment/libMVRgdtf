//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#include "Prefix/StdAfx.h"

#if _LINUX
	// If this include fails, run this command to install it:
	// sudo apt-get install uuid-dev
	#include <uuid/uuid.h>
#endif

#if _ANDROID
	#include <memory>
#endif

// GUID stuff
#ifdef _WINDOWS
namespace windows {
	// NOTE!
	// NOTE!
	// NOTE! You have to import library 'Rpcrt4.lib' for this to be used !!!
	#include <Rpc.h>
}
#else

#endif

using namespace VectorworksMVR::VWFC;


VWFC::Tools::VWUUID::VWUUID(Uint32 a, Uint32 b, Uint32 c, Uint32 d)
{
	fData[0]			= (Uint8) (a & 0xFF);
	fData[1]			= (Uint8) ((a >> 8) & 0xFF);
	fData[2]			= (Uint8) ((a >> 16) & 0xFF);
	fData[3]			= (Uint8) ((a >> 24) & 0xFF);
	fData[4]			= (Uint8) (b & 0xFF);
	fData[5]			= (Uint8) ((b >> 8) & 0xFF);
	fData[6]			= (Uint8) ((b >> 16) & 0xFF);
	fData[7]			= (Uint8) ((b >> 24) & 0xFF);
	fData[8]			= (Uint8) (c & 0xFF);
	fData[9]			= (Uint8) ((c >> 8) & 0xFF);
	fData[10]			= (Uint8) ((c >> 16) & 0xFF);
	fData[11]			= (Uint8) ((c >> 24) & 0xFF);
	fData[12]			= (Uint8) (d & 0xFF);
	fData[13]			= (Uint8) ((d >> 8) & 0xFF);
	fData[14]			= (Uint8) ((d >> 16) & 0xFF);
	fData[15]			= (Uint8) ((d >> 24) & 0xFF);
}

VWFC::Tools::VWUUID::VWUUID(const Uint8* const pArray, size_t size)
{
	for(size_t i=0; i<16; i++) {
		if ( i < size )	fData[i] = pArray[i];
		else			fData[i] = 0;
	}
}

VWFC::Tools::VWUUID::VWUUID(const VWIID& iid)
{
	fData[3]			= (Uint8) (iid.data1 & 0xFF);
	fData[2]			= (Uint8) ((iid.data1 >> 8) & 0xFF);
	fData[1]			= (Uint8) ((iid.data1 >> 16) & 0xFF);
	fData[0]			= (Uint8) ((iid.data1 >> 24) & 0xFF);

	fData[5]			= (Uint8) (iid.data2 & 0xFF);
	fData[4]			= (Uint8) ((iid.data2 >> 8) & 0xFF);

	fData[7]			= (Uint8) (iid.data3 & 0xFF);
	fData[6]			= (Uint8) ((iid.data3 >> 8) & 0xFF);

	fData[ 8 ]		= iid.data4[0];
	fData[ 9 ]	 	= iid.data4[1];
	fData[ 10 ]	 	= iid.data4[2];
	fData[ 11 ]	 	= iid.data4[3];
	fData[ 12 ]	 	= iid.data4[4];
	fData[ 13 ]	 	= iid.data4[5];
	fData[ 14 ]	 	= iid.data4[6];
	fData[ 15 ]	 	= iid.data4[7];
}

VWFC::Tools::VWUUID::VWUUID(const VWFC::Tools::VWUUID& src)
{
	for(Sint32 i=0; i<2; i++)
		fData64[i] = src.fData64[i];
}

VWFC::Tools::VWUUID::~VWUUID()
{
}

VWFC::Tools::VWUUID& VWFC::Tools::VWUUID::operator=(const VWFC::Tools::VWUUID& src)
{
	for(Sint32 i=0; i<2; i++)
		fData64[i] = src.fData64[i];
	return *this;
}

bool VWFC::Tools::VWUUID::operator==(const VWFC::Tools::VWUUID& id) const
{
	for(Sint32 i=0; i<2; i++) {
		if ( fData64[i] != id.fData64[i] )
			return false;
	}
	return true;
}

bool VWFC::Tools::VWUUID::operator!=(const VWFC::Tools::VWUUID& id) const
{
	return !this->operator==(id);
}

static char GetPieceAsChar(Uint8 piece)
{
	VWFC_ASSERT( piece <= 0x0F );
	char	ch;
	if ( piece <= 9 )
		ch	= '0' + piece;
	else
		ch	= 'A' + (piece - 0x0A);

	return ch;
}

static TXString	GetPieceAsText(Uint8 piece)
{
	char	buffer[3];
	buffer[0]	= ::GetPieceAsChar( piece >> 4 );
	buffer[1]	= ::GetPieceAsChar( piece & 0x0F );
	buffer[2]	= 0x00;

	TXString	str	= buffer;
	return str;
}

static Uint8 GetDigitForChar(char ch)
{
	if ( ch >= '0' && ch <= '9' )
		return ch - '0';
	if ( ch >= 'A' && ch <= 'F' )
		return 0x0A + (ch - 'A');
	if ( ch >= 'a' && ch <= 'f' )
		return 0x0A + (ch - 'a');

	THROW_VWFC_EXCEPTION( kEveryone, 0, "Bad UUID string : bad char" );
	return 0;
}

static Uint8 GetDigitForPiece(const char* pString)
{
	Uint8		a		= ::GetDigitForChar( * (pString + 0) );
	Uint8		b		= ::GetDigitForChar( * (pString + 1) );

	VWFC_ASSERT( a <= 0x0F );
	VWFC_ASSERT( b <= 0x0F );

	Uint8		res		= a << 4 | (b & 0x0F);
	return res;
}

// {09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
VWFC::Tools::VWUUID::operator TXString() const
{
	return ToString(true);
}


TXString VWFC::Tools::VWUUID::ToString(bool includeBrackets) const
{
	TXString	str;
	if ( includeBrackets ) str = "{";
	str					+= ::GetPieceAsText( fData[0] );
	str					+= ::GetPieceAsText( fData[1] );
	str					+= ::GetPieceAsText( fData[2] );
	str					+= ::GetPieceAsText( fData[3] );
	str					+= "-";
	str					+= ::GetPieceAsText( fData[4] );
	str					+= ::GetPieceAsText( fData[5] );
	str					+= "-";
	str					+= ::GetPieceAsText( fData[6] );
	str					+= ::GetPieceAsText( fData[7] );
	str					+= "-";
	str					+= ::GetPieceAsText( fData[8] );
	str					+= ::GetPieceAsText( fData[9] );
	str					+= "-";
	str					+= ::GetPieceAsText( fData[10] );
	str					+= ::GetPieceAsText( fData[11] );
	str					+= ::GetPieceAsText( fData[12] );
	str					+= ::GetPieceAsText( fData[13] );
	str					+= ::GetPieceAsText( fData[14] );
	str					+= ::GetPieceAsText( fData[15] );
	if ( includeBrackets ) {
		str					+= "}";
	}

	return str;
}

bool VWFC::Tools::VWUUID::FromString(const TXString& str, bool includeBrackets)
{
	bool b = str.GetLength() == (includeBrackets ? 38 : 36);

	if ( b ) {
		if(includeBrackets)
		{
			b = str.GetAt(0) == '{' &&
				str.GetAt(9) == '-' &&
				str.GetAt(14) == '-' &&
				str.GetAt(19) == '-' &&
				str.GetAt(24) == '-' &&
				str.GetAt(37) == '}';
		}
		else
		{
			b = str.GetAt(8) == '-' &&
				str.GetAt(13) == '-' &&
				str.GetAt(18) == '-' &&
				str.GetAt(23) == '-';
		}
	}

	if ( b )
	{
		const char* pString		= (const char*) str;

		if(includeBrackets)
		{
			fData[0]		= ::GetDigitForPiece( pString + 1 );
			fData[1]		= ::GetDigitForPiece( pString + 3 );
			fData[2]		= ::GetDigitForPiece( pString + 5 );
			fData[3]		= ::GetDigitForPiece( pString + 7 );
			fData[4]		= ::GetDigitForPiece( pString + 10 );
			fData[5]		= ::GetDigitForPiece( pString + 12 );
			fData[6]		= ::GetDigitForPiece( pString + 15 );
			fData[7]		= ::GetDigitForPiece( pString + 17 );
			fData[8]		= ::GetDigitForPiece( pString + 20 );
			fData[9]		= ::GetDigitForPiece( pString + 22 );
			fData[10]		= ::GetDigitForPiece( pString + 25 );
			fData[11]		= ::GetDigitForPiece( pString + 27 );
			fData[12]		= ::GetDigitForPiece( pString + 29 );
			fData[13]		= ::GetDigitForPiece( pString + 31 );
			fData[14]		= ::GetDigitForPiece( pString + 33 );
			fData[15]		= ::GetDigitForPiece( pString + 35 );
		}
		else
		{
			fData[0]		= ::GetDigitForPiece( pString + 0 );
			fData[1]		= ::GetDigitForPiece( pString + 2 );
			fData[2]		= ::GetDigitForPiece( pString + 4 );
			fData[3]		= ::GetDigitForPiece( pString + 6 );
			fData[4]		= ::GetDigitForPiece( pString + 9 );
			fData[5]		= ::GetDigitForPiece( pString + 11 );
			fData[6]		= ::GetDigitForPiece( pString + 14 );
			fData[7]		= ::GetDigitForPiece( pString + 16 );
			fData[8]		= ::GetDigitForPiece( pString + 19 );
			fData[9]		= ::GetDigitForPiece( pString + 21 );
			fData[10]		= ::GetDigitForPiece( pString + 24 );
			fData[11]		= ::GetDigitForPiece( pString + 26 );
			fData[12]		= ::GetDigitForPiece( pString + 28 );
			fData[13]		= ::GetDigitForPiece( pString + 30 );
			fData[14]		= ::GetDigitForPiece( pString + 32 );
			fData[15]		= ::GetDigitForPiece( pString + 34 );
		}
	}

	return b;
}

VWFC::Tools::VWUUID::VWUUID(const TXString& str)
{
	// {09E95D97-364C-43d5-8ADF-FF4CE0EC41A7}
	if ( !FromString(str))
	{
		// create new UUID if this is not a valid UUID
		VWUUID newUUID;
		*this = newUUID;
	}

}

VWFC::Tools::VWUUID::VWUUID()
{
	fData64[0] = 0;
	fData64[1] = 0;
}

void VWFC::Tools::VWUUID::New()
{
#ifdef _WINDOWS
	GUID	guid;
	using namespace windows;
	UuidCreateSequential( & guid );
	fData[0]			= (Uint8) ((guid.Data1 >> 24) & 0xFF);
	fData[1]			= (Uint8) ((guid.Data1 >> 16) & 0xFF);
	fData[2]			= (Uint8) ((guid.Data1 >> 8) & 0xFF);
	fData[3]			= (Uint8) (guid.Data1 & 0xFF);
	fData[4]			= guid.Data2 >> 8;
	fData[5]			= guid.Data2 & 0xFF;
	fData[6]			= guid.Data3 >> 8;
	fData[7]			= guid.Data3 & 0xFF;
	fData[8]			= guid.Data4[0];
	fData[9]			= guid.Data4[1];
	fData[10]			= guid.Data4[2];
	fData[11]			= guid.Data4[3];
	fData[12]			= guid.Data4[4];
	fData[13]			= guid.Data4[5];
	fData[14]			= guid.Data4[6];
	fData[15]			= guid.Data4[7];
#elif _LINUX
	uuid_t myUUID;
	uuid_generate_time_safe( myUUID );
	memcpy( fData, &myUUID, 16 );
#elif __APPLE__

	auto newId = CFUUIDCreate(kCFAllocatorDefault);
	auto bytes = CFUUIDGetUUIDBytes(newId);
	CFRelease(newId);

	fData[0]  =	bytes.byte0;
	fData[1]  =	bytes.byte1;
	fData[2]  =	bytes.byte2;
	fData[3]  =	bytes.byte3;
	fData[4]  =	bytes.byte4;
	fData[5]  =	bytes.byte5;
	fData[6]  =	bytes.byte6;
	fData[7]  =	bytes.byte7;
	fData[8]  =	bytes.byte8;
	fData[9]  =	bytes.byte9;
	fData[10] =	bytes.byte10;
	fData[11] =	bytes.byte11;
	fData[12] =	bytes.byte12;
	fData[13] =	bytes.byte13;
	fData[14] =	bytes.byte14;
	fData[14] =	bytes.byte15;

#elif _ANDROID

	{
		using namespace VectorworksMVR::Filing;

		IFileIdentifierPtr file (IID_FileIdentifier);

		// This is the only feasible way to get a new uuid on android. 
		// Only alternative is accessing the jvm and using the java crypto class
		// This requires active initialization from the calling java application though
		file->Set("/proc/sys/kernel/random/uuid");

		Uint64 size = 0;
		IRawOSFilePtr rawFile (IID_RawOSFile);
		rawFile->Open(file, true, false, true, false);
		rawFile->GetFileSize(size);
		std::unique_ptr<char> storage(new char[size]);
		rawFile->Read(0, size, storage.get());
		rawFile->Close();
		TXString st(storage.get(), size);
		FromString(st, false);
	}

#endif

}

void VWFC::Tools::VWUUID::GetUUID(Uint32& out1, Uint32& out2, Uint32& out3, Uint32& out4) const
{
   out1 = (Uint32) ( fData[0] + fData[1] * 256 + fData[2] * 65536 + fData[3] * 16777216 );
   out2 = (Uint32) ( fData[4] + fData[5] * 256 + fData[6] * 65536 + fData[7] * 16777216 );
   out3 = (Uint32) ( fData[8] + fData[9] * 256 + fData[10] * 65536 + fData[11] * 16777216 );
   out4 = (Uint32) ( fData[12] + fData[13] * 256 + fData[14] * 65536 + fData[15] * 16777216 );
}

void VWFC::Tools::VWUUID::GetUUID(Uint8* pArray, size_t size) const
{
	for(size_t i=0; i<size; i++) {
		if ( i >= 16 )
			pArray[ i ]	= 0;
		else
			pArray[ i ]	= fData[ i ];
	}
}

void VWFC::Tools::VWUUID::GetUUID(VWIID& out) const
{
    out.data1		= (Sint32)  ( fData[3] + fData[2] * 256 + fData[1] * 65536 + fData[0] * 16777216 );
    out.data2		= (short) ( fData[5] + fData[4] * 256);
    out.data3		= (short) ( fData[7] + fData[6] * 256);
    out.data4[0]	= fData[ 8 ];
	out.data4[1]	= fData[ 9 ];
	out.data4[2]	= fData[ 10 ];
	out.data4[3]	= fData[ 11 ];
	out.data4[4]	= fData[ 12 ];
	out.data4[5]	= fData[ 13 ];
	out.data4[6]	= fData[ 14 ];
	out.data4[7]	= fData[ 15 ];
}

TXString VWFC::Tools::VWUUID::Encode(const TXString& arrChars) const
{
	const size_t	validCharsCount	= arrChars.GetLength();
	const size_t	extractCount	= 6;

	Uint32				nums[4];
	this->GetUUID( nums[0], nums[1], nums[2], nums[3] );
	char				szBuffer[ 4 * extractCount + 1 ];
	for(size_t iNum=0; iNum<4; iNum++) {
		size_t		thisNum	= nums[ iNum ];
		for(size_t count=0; count<extractCount; count++) {
			size_t		index		= thisNum % validCharsCount;
			thisNum					= thisNum / validCharsCount;

			szBuffer[extractCount*iNum + count]	= (char)arrChars.GetAt( index );
		}
	}
	szBuffer[ 4 * extractCount ]	= 0x00;

	return szBuffer;
}
