// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpResponce.generated.h"


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
class TC_HTTPSERVER_API UHttpResponce : public UObject
{
	GENERATED_BODY()
	

public:
	//UHttpResponce(){}
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	FString Parse(const TMap<FString, FString>& str);
	FString Parse_Implementation(const TMap<FString, FString>& str);

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="HttpServer")
	FString HttpPath;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="HttpServer")
	EHttpType HttpType = EHttpType::Get;
};
