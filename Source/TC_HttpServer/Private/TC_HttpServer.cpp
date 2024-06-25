// Copyright Epic Games, Inc. All Rights Reserved.

#include "TC_HttpServer.h"



#define LOCTEXT_NAMESPACE "FTC_HttpServerModule"

void FTC_HttpServerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FTC_HttpServerModule::ShutdownModule()
{
	//FJsonObjectWrapper
	
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_GAME_MODULE(FTC_HttpServerModule, TC_HttpServer)