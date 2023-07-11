//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Include/VectorworksMVR.h"

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define IS64BIT
#else
#define IS32BIT
#endif
#else
#if (INTPTR_MAX == INT32_MAX)
# define IS32BIT
#else
# define IS64BIT
#endif
#endif


struct UnittestFailObject
{
    std::string fMessage;
};
typedef std::vector<UnittestFailObject> TUnittestFailArray;


class Unittest
{
public:
    Unittest();
    virtual ~Unittest();

public:
    bool RunTest();

    void checkifTrue(const std::string & check, const bool b);

protected:
    bool virtual ExecuteTest() = 0;


public:
    void checkifEqual(const std::string& check, const Uint32 val1, const Uint32 val2);
	void checkifEqual(const std::string& check, const Sint32 val1, const Sint32 val2);
	void checkifEqual(const std::string& check, const Uint8	 val1, const Uint8  val2);
	void checkifEqual(const std::string& check, const double val1, const double val2);
#if defined GS_MAC 
	void checkifEqual(const std::string& check, const size_t val1, const size_t val2);
#endif
	void checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::DmxValue val1, const VectorworksMVR::GdtfDefines::DmxValue val2);

    void checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::DMXAddress val1, const VectorworksMVR::GdtfDefines::DMXAddress val2);
    void checkifEqualPtr(const std::string& check, void* val1, void* val2);
	void checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::EGdtfModel_PrimitiveType val1, const VectorworksMVR::GdtfDefines::EGdtfModel_PrimitiveType val2);
    void checkifEqual(const std::string& check, const std::string& val1, const std::string& val2);
    void checkifEqual(const std::string& check, const VectorworksMVR::MvrUUID val1, const VectorworksMVR::MvrUUID val2);
    void checkifEqual(const std::string& check, const VectorworksMVR::CieColor val1, const VectorworksMVR::CieColor val2);
    void checkifEqual(const std::string& check, const VectorworksMVR::RGBColor val1, const VectorworksMVR::RGBColor val2);

    bool checkVCOM(VectorworksMVR::VCOMError error, const std::string& check);
    bool checkVCOM_NotSet(VectorworksMVR::VCOMError error, const std::string& check);
	bool checkVCOM_Failed(VectorworksMVR::VCOMError error, const std::string& check);
    void PrintParsingError(const std::string& check, const Sint32 val1, size_t line, size_t column);


    void PrintParsingErrorList(VectorworksMVR::IGdtfFixturePtr& fixture);

    template <typename A>
    void checkifUnEqual(const std::string& check, A result, A expected)
    {
        if (result != expected) return;

        // Else Log the error
        fFailed = true;

        UnittestFailObject test;
        test.fMessage += check;
        test.fMessage += " Result: ";
        test.fMessage += std::to_string(result);
        test.fMessage += " Expected: ";
        test.fMessage += std::to_string(expected);

        fFailedTests.push_back(test);
    };
    void checkifUnEqual(const std::string& check, const VectorworksMVR::MvrUUID val1, const VectorworksMVR::MvrUUID val2);

    bool Equalish(double val1, double val2, double epislon);

	// For clearing false state if false error was forced
	size_t                      	getFailedTestCount();
	void							resetFailedTestState();
private:
    bool                fFailed;
    TUnittestFailArray  fFailedTests;

};

