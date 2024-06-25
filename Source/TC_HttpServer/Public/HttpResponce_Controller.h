// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpResponce_Controller.generated.h"


UENUM(Blueprintable)
enum class EHttpType : uint8
{
	Get,
	Post,
};
/**
 *
 */
UCLASS(Blueprintable)
class TC_HTTPSERVER_API UHttpResponce_Controller : public UObject
{
	GENERATED_BODY()
public:
	//蓝图去匹配
	///UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	virtual  FString Parse(const TMap<FString, FString>& map_param);
	//或者C++实现
	//virtual  FString Parse_Implementation(const TMap<FString, FString>& map_param);

	

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="HttpServer")
	FString HttpPath;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="HttpServer")
	EHttpType HttpType = EHttpType::Get;
	
};
