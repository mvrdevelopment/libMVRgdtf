//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"
#include "GdtfUnittestHandler.h"


class GdtfLineNumberParseErrorTest : public Unittest
{
public:
	GdtfLineNumberParseErrorTest(const std::string& currentDir);
	virtual ~GdtfLineNumberParseErrorTest();
protected:
	bool virtual ExecuteTest();

private:
	void ReadFile();
	void ClearExpectedError();

	std::string fErrorGdtf_Path;
};