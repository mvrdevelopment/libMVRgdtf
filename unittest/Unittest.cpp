//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include <iostream>
#include <cmath>

using namespace VectorworksMVR;

Unittest::Unittest()
{
    fFailed = false;
};

Unittest::~Unittest()
{
};

bool Unittest::RunTest()
{
    std::cout << "============================================================================================" << std::endl;
    this->ExecuteTest();

   for(size_t i = 0; i < fFailedTests.size(); i++)
   {
       std::cout << fFailedTests[i].fMessage << std::endl;
   }
   
if(fFailed)
{
	std::cout << "                                           FAILED                                          =" << std::endl;
}
else
{
	std::cout << "=                                         SUCCEEDED                                        =" << std::endl;
}
	std::cout << "============================================================================================" << std::endl;
    return fFailed;
}

void Unittest::checkifTrue (const std::string& check, const bool b) 
{
    checkifEqual(check, b, true);
}
void Unittest::checkifEqual(const std::string& check, const Uint32 val1, const Uint32 val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Expected: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const Sint32 val1, const Sint32 val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Expected: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};



void Unittest::checkifEqual(const std::string& check, const Uint8 val1, const Uint8 val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Expected: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};


void Unittest::checkifEqual(const std::string& check, const double val1, const double val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Expected: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};

#ifdef GS_MAC
void Unittest::checkifEqual(const std::string& check, const size_t val1, const size_t val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Expected: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};
#endif

 // Read comment at declaration!
void Unittest::checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::DmxValue val1, const VectorworksMVR::GdtfDefines::DmxValue val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Expected: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::DMXAddress val1, const VectorworksMVR::GdtfDefines::DMXAddress val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Expected: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::EGdtfModel_PrimitiveType val1, const VectorworksMVR::GdtfDefines::EGdtfModel_PrimitiveType val2)
{
	if ( val1 == val2 ) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Expected: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const VectorworksMVR::MvrUUID val1, const VectorworksMVR::MvrUUID val2)
{
	if ( val1.a == val2.a && val1.b == val2.b && val1.c == val2.c && val1.d == val2.d) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val1.a)+".";
	test.fMessage += std::to_string(val1.b)+".";
	test.fMessage += std::to_string(val1.c)+".";
	test.fMessage += std::to_string(val1.d);
	test.fMessage += " Expected: ";
	test.fMessage += std::to_string(val2.a)+".";
	test.fMessage += std::to_string(val2.b)+".";
	test.fMessage += std::to_string(val2.c)+".";
	test.fMessage += std::to_string(val2.d);

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const VectorworksMVR::CieColor val1, const VectorworksMVR::CieColor val2)
{
	if ( val1.fx == val2.fx && val1.fy == val2.fy && val1.f_Y == val2.f_Y ) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += "(" + std::to_string(val1.fx) + "), ";
	test.fMessage += "(" + std::to_string(val1.fy) + "), ";
	test.fMessage += "(" + std::to_string(val1.f_Y) + "), ";
	test.fMessage += " Expected: ";
	test.fMessage += "(" + std::to_string(val2.fx) + "), ";
	test.fMessage += "(" + std::to_string(val2.fy) + "), ";
	test.fMessage += "(" + std::to_string(val2.f_Y) + "), ";

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const VectorworksMVR::RGBColor val1, const VectorworksMVR::RGBColor val2)
{
	if ( Equalish(val1.r,val2.r,1) && Equalish(val1.g,val2.g,1) && Equalish(val1.b,val2.b,1) ) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += "(" + std::to_string(val1.r) + "), ";
	test.fMessage += "(" + std::to_string(val1.g) + "), ";
	test.fMessage += "(" + std::to_string(val1.b) + "), ";
	test.fMessage += " Expected: ";
	test.fMessage += "(" + std::to_string(val2.r) + "), ";
	test.fMessage += "(" + std::to_string(val2.g) + "), ";
	test.fMessage += "(" + std::to_string(val2.b) + "), ";

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const std::string& aspected, const std::string& result)
{
	if (aspected == result) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += aspected;
	test.fMessage += " Expected: ";
	test.fMessage += result;

	fFailedTests.push_back(test);

};

bool Unittest::checkVCOM(VectorworksMVR::VCOMError error, const std::string& check)
{
    if(kVCOMError_NoError == error) return true;

    // Else Log the error
    fFailed = true;

    UnittestFailObject test;
    test.fMessage += "VCOM Failed: ";
    test.fMessage += check;
    test.fMessage += " Return Value: ";
    test.fMessage += std::to_string(error);

    fFailedTests.push_back(test);

    return false;
};

bool Unittest::checkVCOM_NotSet(VectorworksMVR::VCOMError error, const std::string& check)
{
    if(kVCOMError_NotSet == error) return true;

    // Else Log the error
    fFailed = true;

    UnittestFailObject test;
    test.fMessage += "VCOM NotSet Failed: ";
    test.fMessage += check;
    test.fMessage += " Return Value: ";
    test.fMessage += std::to_string(error);;

    fFailedTests.push_back(test);

    return false;
};

bool Unittest::checkVCOM_Failed(VectorworksMVR::VCOMError error, const std::string& check)
{
	if (kVCOMError_NoError != error) return true;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += "VCOM Failed FAILED: ";
	test.fMessage += check;
	test.fMessage += " Return Value: ";
	test.fMessage += std::to_string(error);;

	fFailedTests.push_back(test);

	return false;
};


void Unittest::checkifEqualPtr(const std::string& check, void* val1, void* val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += (Uint64)val1;
	test.fMessage += " Expected: ";
	test.fMessage += (Uint64)val1;

	fFailedTests.push_back(test);
};

void Unittest::PrintParsingError(const std::string& check, const Sint32 val1, size_t line, size_t column)
{
	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += " Code: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Message: ";
	test.fMessage += check;
	test.fMessage += " Line: ";
	test.fMessage += std::to_string(line) ;
	test.fMessage += " Column: ";
	test.fMessage += std::to_string(column);

	fFailedTests.push_back(test);
};

void Unittest::PrintParsingErrorList(VectorworksMVR::IGdtfFixturePtr& fixture)
{
	// Print Parsing Errors
	size_t countParsingErrors = 0;
	fixture->GetParsingErrorCount(countParsingErrors);
	for(size_t i = 0; i < countParsingErrors; i++)
	{
		GdtfDefines::EGdtfParsingError errorType;
		
		size_t line   = 0;
		size_t column = 0;

		IGdtfXmlParsingErrorPtr error;
		fixture->GetParsingErrorAt( i, &error);
		error->GetErrorType(errorType);
		error->GetLineAndColumnNumber(line, column);
		PrintParsingError(error->GetErrorMessage(), (Sint32)errorType, line, column);
	}
};

void Unittest::checkifUnEqual(const std::string& check, const VectorworksMVR::MvrUUID val1, const VectorworksMVR::MvrUUID val2)
{
	if ( ! (val1.a == val2.a && val1.b == val2.b && val1.c == val2.c && val1.d == val2.d)) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val1.a)+".";
	test.fMessage += std::to_string(val1.b)+".";
	test.fMessage += std::to_string(val1.c)+".";
	test.fMessage += std::to_string(val1.d);
	test.fMessage += " Expected: ";
	test.fMessage += std::to_string(val2.a)+".";
	test.fMessage += std::to_string(val2.b)+".";
	test.fMessage += std::to_string(val2.c)+".";
	test.fMessage += std::to_string(val2.d);

	fFailedTests.push_back(test);
};

bool Unittest::Equalish(double val1, double val2, double epislon)
{
	return (std::abs(val1 - val2) <= epislon);
}


size_t Unittest::getFailedTestCount()
{
    return fFailedTests.size();
}

void Unittest::resetFailedTestState()
{
	fFailed = false;
}
