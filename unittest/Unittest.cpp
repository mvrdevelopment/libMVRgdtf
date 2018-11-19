//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include <iostream>

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
    std::cout << "======================================================" << std::endl;
    this->ExecuteTest();

   
   
   for(size_t i = 0; i < fFailedTests.size(); i++)
   {
       std::cout << fFailedTests[i].fMessage << std::endl;
   }
   
if(fFailed)
{
	std::cout << "=                      FAILED                        =" << std::endl;
}
else
{
	std::cout << "=                     SUCCEEDED                      =" << std::endl;
}
	std::cout << "======================================================" << std::endl;
    return fFailed;
}

void Unittest::checkifEqual(const std::string& check, const Uint32 val1, const Uint32 val2)
{
    if(val1 == val2) return;

    // Else Log the error
    fFailed = true;

    UnittestFailObject test;
    test.fMessage += check;
    test.fMessage += "Aspected: ";
    test.fMessage += std::to_string(val1);
    test.fMessage += " Result: ";
    test.fMessage += std::to_string(val2);

    fFailedTests.push_back(test);

};

void Unittest::checkifEqual(const std::string& check, const size_t val1, const size_t val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += "Aspected: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);

};


void Unittest::checkifEqual(const std::string& check, const std::string& val1, const std::string& val2)
{
    if(val1 == val2) return;

    // Else Log the error
    fFailed = true;

    UnittestFailObject test;
    test.fMessage += check;
    test.fMessage += "Aspected: ";
    test.fMessage += val1;
    test.fMessage += " Result: ";
    test.fMessage += val2;

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
    test.fMessage += " Result: ";
    test.fMessage += error;

    fFailedTests.push_back(test);

    return false;

};