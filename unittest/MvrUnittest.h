//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"

using VectorworksMVR::IMediaRessourceVectorInterfacePtr;
using VectorworksMVR::ISceneObjPtr;

class MvrUnittest : public Unittest
{
public:
    MvrUnittest(const std::string& currentDir);
    virtual ~MvrUnittest();
protected:
    bool virtual ExecuteTest();

private:
    void        WriteFile();
    void        ReadFile();
    std::string GetTestWheel_PNG(bool readLocation);
    void Write_NestedObjects(IMediaRessourceVectorInterfacePtr, ISceneObjPtr layer);
    void Read_TestGroup(IMediaRessourceVectorInterfacePtr interf, ISceneObjPtr layer);
    void Read_NestedObjects(IMediaRessourceVectorInterfacePtr interf, ISceneObjPtr layer);
    bool verifyFirstChildType(IMediaRessourceVectorInterfacePtr interf, ISceneObjPtr obj, VectorworksMVR::ESceneObjType exptectedTyp);
    bool Read_NestedObjectsInTruss(IMediaRessourceVectorInterfacePtr interf, ISceneObjPtr truss);

    std::string fPath;
	std::string gdtfPath;
};