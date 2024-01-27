// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMyPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
    
    void AddMenuRow(FMenuBuilder& MenuBuilder);
    void FillSubmenu(FMenuBuilder& MenuBuilder);
    void MenuCallback();
};
