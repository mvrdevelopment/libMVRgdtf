#include "Prefix/StdAfx.h"

#include "UTranslateFiles.h"


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
