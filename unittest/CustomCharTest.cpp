//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------

#include "Include/VectorworksMVR.h"
#include "CustomCharTest.h"
#include "Utility.h"


using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)

GdtfCustomCharTest::GdtfCustomCharTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
}

GdtfCustomCharTest::~GdtfCustomCharTest()
{  
}


std::string GdtfCustomCharTest::GetUnitTestName()
{  
    return  std::string("GdtfCustomCharTest");
}

void GdtfCustomCharTest::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    IGdtfWheelPtr wheel;
    fixture->CreateWheel("Wheel", &wheel);

    IGdtfWheelSlotPtr slot;
    wheel->CreateWheelSlot("SlotName", &slot);

    slot->SetGobo("屏幕快照 2019-03-29 下午2.52.35");

    std::string path = UnitTestUtil::GetTestResourceFolder() + kSeparator + "屏幕快照 2019-03-29 下午2.52.35.png";
    fixture->AddFileToGdtfFile(path.c_str(), ERessourceType::ImageWheel);
}

void GdtfCustomCharTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{  
    IGdtfWheelPtr wheel;
    fixture->GetWheelAt(0, &wheel);

    IGdtfWheelSlotPtr slot;
    wheel->GetWheelSlotAt(0, &slot);

    std::string goboName = slot->GetGobo();
    checkifEqual("Gobo Name", goboName, "屏幕快照 2019-03-29 下午2.52.35");


    this->checkifTrue("Gobo Image exists", UnitTestUtil::FileExists (slot->GetGoboFileFullPath()) );


}
