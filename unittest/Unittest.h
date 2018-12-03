//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Include/VectorworksMVR.h"

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

protected:
    bool virtual ExecuteTest() = 0;


public:
    void checkifEqual(const std::string& check, const Uint32 val1, const Uint32 val2);
	void checkifEqual(const std::string& check, const Sint32 val1, const Sint32 val2);
	void checkifEqual(const std::string& check, const double val1, const double val2);
	void checkifEqual(const std::string& check, const size_t val1, const size_t val2);
#ifdef GS_MAC
	// Under Win and Linux there is a problem with double declaration of DMXValue (Uint64 type) and size_t (also Uint64 type)
	// OSX needs that extra declaration
	void checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::DmxValue val1, const VectorworksMVR::GdtfDefines::DmxValue val2);
#endif
    void checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::DMXAddress val1, const VectorworksMVR::GdtfDefines::DMXAddress val2);
    void checkifEqualPtr(const std::string& check, void* val1, void* val2);
	//void checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::DmxValue val1, const VectorworksMVR::GdtfDefines::DmxValue val2);
	//void checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::DMXAddress val1, const VectorworksMVR::GdtfDefines::DMXAddress val2);
	void checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::EGdtfModel_PrimitiveType val1, const VectorworksMVR::GdtfDefines::EGdtfModel_PrimitiveType val2);
    void checkifEqual(const std::string& check, const std::string& val1, const std::string& val2);
    bool checkVCOM(VectorworksMVR::VCOMError error, const std::string& check);
    bool checkVCOM_NotSet(VectorworksMVR::VCOMError error, const std::string& check);


private:
    bool                fFailed;
    TUnittestFailArray  fFailedTests;

};

