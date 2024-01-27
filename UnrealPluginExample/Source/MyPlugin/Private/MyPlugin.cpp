// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyPlugin.h"
#include "LevelEditor.h"


// Include mvrGDTF
#define _LINUX 0
#include "Include/VectorworksMVR.h"

#define LOCTEXT_NAMESPACE "FMyPluginModule"



static bool showError() {
    UE_LOG(LogTemp, Error, TEXT("MVR ERROR"));
    return false;
}
                        
                        
#define         MVR_SUCCEEDED(x)                (x == VectorworksMVR::kVCOMError_NoError) ? true : showError()




using namespace VectorworksMVR;

void FMyPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    UE_LOG(LogTemp, Warning, TEXT("THE MODULE DID JSUT START!"));
    
    
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
    
    
    
    TSharedPtr<FExtender> menuExtender = MakeShareable(new FExtender());
    menuExtender->AddMenuExtension(
                                  "EditMain",
                                  EExtensionHook::After,
                                  NULL,
                                  FMenuExtensionDelegate::CreateRaw(this, &FMyPluginModule::AddMenuRow)
                                  );
    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(menuExtender);
}

void FMyPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FMyPluginModule::AddMenuRow(FMenuBuilder& MenuBuilder)
{
    MenuBuilder.BeginSection("Custom Menu", TAttribute<FText>(FText::FromString("Category/Section Name")));
    {
        MenuBuilder.AddSubMenu(FText::FromString("My Submenu"),
                               FText::FromString("My submenu tooltip"),
                               FNewMenuDelegate::CreateRaw(this, &FMyPluginModule::FillSubmenu));
    }
    MenuBuilder.EndSection();
}

void FMyPluginModule::FillSubmenu(FMenuBuilder& MenuBuilder)
{
    MenuBuilder.AddMenuEntry(
                             FText::FromString("Menu Entry 1"),
                             FText::FromString("Menu Entry 1 tooltip"),
                             FSlateIcon(),
                             FUIAction(FExecuteAction::CreateRaw(this, &FMyPluginModule::MenuCallback))
                             );
}

void FMyPluginModule::MenuCallback()
{
    UE_LOG(LogTemp, Warning, TEXT("MENU WORKING"));
    
    // Import MVR
    
    IMediaRessourceVectorInterfacePtr mvrFileForRead (IID_MediaRessourceVectorInterface);
    if (MVR_SUCCEEDED(mvrFileForRead->OpenForRead("/Users/lucaherzke/Documents/NormalTest.mvr")))
    {
        UE_LOG(LogTemp, Warning, TEXT("SUCCESFULLY IMPORTED MVR"));
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyPluginModule, MyPlugin)
