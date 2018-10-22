#include "StdAfx.h"

#include "UTranslateFiles.h"

#if GS_WIN

#elif GS_LIN

#else
// we fake this implementation for the stand alone app
// it is provided by Vectorworks when running as a plugin
@implementation NSString (NNAStringCategory)


+ (NSString*)stringWithTXString:(const TXString &)txs
{
	return [NSString stringWithCharacters:txs.GetData()
								   length:txs.GetLength()];
}

- (TXString)toTXString
{
	int len = [self length];
	unichar buffer[len + 1];
	[self getCharacters:buffer
				  range:NSMakeRange(0,len)];
	buffer[len] = 0;
	return TXString(buffer);
}

@end

TXString GetDisplayStringForPath(const TXString& path)
{
	@autoreleasepool
	{
		NSString*			displayStr	= @"";
		TXString			retVal		= path;

		NSString* pathNSString = [NSString stringWithTXString:path];
		NSArray* pathComponents = [[NSFileManager defaultManager] componentsToDisplayForPath:pathNSString];

		if (pathComponents)
		{
			for (int i=0; i<[pathComponents count]; i++)
			{
				displayStr = [displayStr stringByAppendingPathComponent:[pathComponents objectAtIndex:i]];
			}

			retVal = [displayStr toTXString];
		}

		return retVal;
	}
}
#endif

TXString FormatFilename(const TXString& stringIn, short maxCharactersWithoutSpace)
//
// Add spaces to a TXString every x characters if spaces don't already exist.   [MAF 4/12/02]
//
{
	// Even though paths can be longer than 255 chars, the LM controls
	// that these paths are displayed in can only handle 255 chars (since
	// they pass values through Pascal strings).  Therefore, this function
	// must truncate the front of the string with an ellipsis if it is too long. [MGD 06/05/07]

	TXString xStringIn(stringIn);

#if GS_WIN

#elif GS_LIN

#else
	xStringIn = GetDisplayStringForPath(xStringIn);
#endif

	short contiguousCharacters      = 0;

	TXString formattedString;

	size_t strLength = xStringIn.GetLength();
	size_t i = 0;
	if (strLength > 250) {
		formattedString << "...";
		i = xStringIn.GetLength() - 250;
	}

	for ( ; i < strLength; i++) {
		if (xStringIn.GetAt(i) == ' ')
			contiguousCharacters = 0;
		else {
			contiguousCharacters++;

			if (contiguousCharacters >= maxCharactersWithoutSpace) {
				formattedString += ' ';
				contiguousCharacters = 0;
			}
		}

		formattedString += xStringIn.GetAt(i);
	}

	return formattedString;
}
