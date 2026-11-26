//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "ParallelMvrTest.h"
#include "Utility.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <map>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;

#define __checkVCOM(x) this->checkVCOM(x, #x)

static const size_t kAttachedFileCount = 40;

static bool ReadWholeFile(const std::string& path, std::string& outContent)
{
	std::ifstream file(path, std::ios::binary);
	if ( ! file) { return false; }

	outContent.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	return true;
}

static std::string AttachedFileName(size_t index)
{
	return "attached_" + std::to_string(index) + ".txt";
}

static std::string AttachedFileContent(size_t index)
{
	return "content of attached file " + std::to_string(index);
}

ParallelMvrTest::ParallelMvrTest(const std::string& currentDir)
{
	fMvrPath = currentDir + kSeparator + "parallelMvrTest.mvr";
	std::cout << "Export File to " << fMvrPath << std::endl;
}

ParallelMvrTest::~ParallelMvrTest()
{
}

bool ParallelMvrTest::ExecuteTest()
{
	std::cout << "=                                        ParallelMvrTest                              =" << std::endl;
	WriteFile();

	std::vector<std::string> withoutPreload;
	std::vector<std::string> withPreload;
	ReadFile(false,	withoutPreload);
	ReadFile(true,	withPreload);

	checkifEqual("Fixture count without preload",	(Sint32)withoutPreload.size(),	Sint32(6));
	checkifEqual("Fixture count with preload",		(Sint32)withPreload.size(),		Sint32(6));
	for (size_t i = 0; i < withoutPreload.size() && i < withPreload.size(); i++)
	{
		checkifEqual("Preload returns the same data #" + std::to_string(i), withPreload[i], withoutPreload[i]);
	}

	return true;
}

void ParallelMvrTest::WriteFile()
{
	const std::string gdtfFiles[] =
	{
		UnitTestUtil::GetTestResourceFolder() + kSeparator + "allWorking.gdtf",
		UnitTestUtil::GetTestResourceFolder() + kSeparator + "BugInChannelSetDmxJumps.gdtf",
		UnitTestUtil::GetTestResourceFolder() + kSeparator + "Robe lighting s.r.o.@BMFL Spot@cannot assign 0 to frost function.gdtf",
	};
	const char* gdtfNamesInMvr[]	= { "GdtfA.gdtf", "GdtfB.gdtf", "GdtfC.gdtf" };

	// GdtfC is referenced without extension, like some exporters do
	const char* fixtureGdtfNames[]	= { "GdtfA.gdtf", "GdtfB.gdtf", "GdtfA.gdtf", "GdtfC", "GdtfB.gdtf", "GdtfA.gdtf" };

	IMediaRessourceVectorInterfacePtr mvrWrite (IID_MediaRessourceVectorInterface);
	if ( ! __checkVCOM(mvrWrite->OpenForWrite(fMvrPath.c_str()))) { return; }

	ISceneObjPtr layer = nullptr;
	__checkVCOM(mvrWrite->CreateLayerObject(MvrUUID(1600000001, 1600000002, 1600000003, 1600000004), "Parallel Layer", &layer));

	for (size_t i = 0; i < 6; i++)
	{
		ISceneObjPtr fixture = nullptr;
		std::string name = "Fixture " + std::to_string(i);
		if (__checkVCOM(mvrWrite->CreateFixture(MvrUUID(1700000000 + (Uint32)i, 1700000100, 1700000200, 1700000300), STransformMatrix(), name.c_str(), layer, &fixture)))
		{
			__checkVCOM(fixture->SetGdtfName(fixtureGdtfNames[i]));
		}
	}

	for (size_t i = 0; i < 3; i++)
	{
		std::string content;
		checkifTrue("Read GDTF test file " + gdtfFiles[i], ReadWholeFile(gdtfFiles[i], content));
		if ( ! content.empty())
		{
			__checkVCOM(mvrWrite->AddBufferToMvrFile(gdtfNamesInMvr[i], &content[0], content.size()));
		}
	}

	for (size_t i = 0; i < kAttachedFileCount; i++)
	{
		std::string content = AttachedFileContent(i);
		__checkVCOM(mvrWrite->AddBufferToMvrFile(AttachedFileName(i).c_str(), &content[0], content.size()));
	}

	// Duplicate entry name: like with sequential writing, the first entry wins.
	std::string duplicate = "this duplicate must not be written";
	__checkVCOM(mvrWrite->AddBufferToMvrFile(AttachedFileName(0).c_str(), &duplicate[0], duplicate.size()));

	__checkVCOM(mvrWrite->Close());
}

void ParallelMvrTest::ReadFile(bool preload, std::vector<std::string>& outFixtureSummary)
{
	const std::string prefix = preload ? "[preload] " : "[no preload] ";

	IMediaRessourceVectorInterfacePtr mvrRead (IID_MediaRessourceVectorInterface);
	if ( ! __checkVCOM(mvrRead->OpenForRead(fMvrPath.c_str()))) { return; }

	if (preload) { __checkVCOM(mvrRead->PreloadGdtfFixtures()); }

	//------------------------------------------------------------------------------------------------
	// Attached files: 3 GDTFs + kAttachedFileCount files, the duplicate is not in the archive
	size_t attachedCount = 0;
	__checkVCOM(mvrRead->GetAttachedFileCount(attachedCount));
	checkifEqual(prefix + "Attached file count", (Sint32)attachedCount, (Sint32)(kAttachedFileCount + 3));

	std::map<std::string, std::string> attachedPathByName;
	for (size_t i = 0; i < attachedCount; i++)
	{
		std::string fullPath	= mvrRead->GetAttachedFileCountAt(i);
		size_t		separator	= fullPath.find_last_of("/\\");
		attachedPathByName[separator == std::string::npos ? fullPath : fullPath.substr(separator + 1)] = fullPath;
	}

	for (size_t i = 0; i < kAttachedFileCount; i++)
	{
		auto it = attachedPathByName.find(AttachedFileName(i));
		checkifTrue(prefix + "Attached file exists " + AttachedFileName(i), it != attachedPathByName.end());
		if (it == attachedPathByName.end()) { continue; }

		std::string content;
		checkifTrue(prefix + "Attached file readable " + AttachedFileName(i), ReadWholeFile(it->second, content));
		checkifEqual(prefix + "Attached file content " + AttachedFileName(i), content, AttachedFileContent(i));
	}

	//------------------------------------------------------------------------------------------------
	// Fixtures
	std::map<std::string, IGdtfFixture*>	fixtureByGdtfName;
	std::vector<IGdtfFixturePtr>			keepAlive;

	ISceneObjPtr layer = nullptr;
	__checkVCOM(mvrRead->GetFirstLayer(&layer));
	if (layer)
	{
		ISceneObjPtr sceneObj = nullptr;
		__checkVCOM(mvrRead->GetFirstChild(layer, &sceneObj));

		while (sceneObj)
		{
			std::string gdtfName = sceneObj->GetGdtfName();

			IGdtfFixturePtr gdtfFixture;
			if (__checkVCOM(sceneObj->GetGdtfFixture(&gdtfFixture)) && gdtfFixture)
			{
				size_t modeCount = 0;
				__checkVCOM(gdtfFixture->GetDmxModeCount(modeCount));
				outFixtureSummary.push_back(gdtfName + "|" + gdtfFixture->GetName() + "|" + std::to_string(modeCount));

				auto it = fixtureByGdtfName.find(gdtfName);
				if (it == fixtureByGdtfName.end())
				{
					for (const auto& other : fixtureByGdtfName)
					{
						checkifTrue(prefix + "Different GDTFs give different fixtures", other.second != static_cast<IGdtfFixture*>(gdtfFixture));
					}
					fixtureByGdtfName[gdtfName] = static_cast<IGdtfFixture*>(gdtfFixture);
				}
				else if (preload)
				{
					checkifTrue(prefix + "Same GDTF gives the cached fixture " + gdtfName, it->second == static_cast<IGdtfFixture*>(gdtfFixture));
				}
				else
				{
					checkifTrue(prefix + "Same GDTF gives a new fixture " + gdtfName, it->second != static_cast<IGdtfFixture*>(gdtfFixture));
				}

				keepAlive.push_back(gdtfFixture);
			}

			ISceneObjPtr next = nullptr;
			mvrRead->GetNextObject(sceneObj, &next);
			sceneObj = next;
		}
	}

	checkifEqual(prefix + "Distinct GDTFs", (Sint32)fixtureByGdtfName.size(), Sint32(3));
}
