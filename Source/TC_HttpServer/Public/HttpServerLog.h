// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
//using Error = ELogVerbosity::Type;

TC_HTTPSERVER_API DECLARE_LOG_CATEGORY_EXTERN(HttpServer_Log,Log,All);

//日志
#define HTTP_SERVER_LOG(Format, ...) \
UE_LOG(HttpServer_Log,Log,Format,##__VA_ARGS__)

//错误日志
#define HTTP_SERVER_ERROR(Format, ...) \
UE_LOG(HttpServer_Log,Error,Format,##__VA_ARGS__)


