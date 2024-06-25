#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonObjectWrapper.h"
#include "Json_Helper.generated.h"







UCLASS(Blueprintable)
class TC_HTTPSERVER_API UJson_Helper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable /*,Category = "HttpServer"*/)
	//这里特殊因为是结构体

	UFUNCTION(BlueprintCallable,Category = "HttpServer")
	static FJsonObjectWrapper Create_Http_ResponseData_Json(int32 Code,FString Msg);
	/*
	UFUNCTION(BlueprintCallable,Category = "HttpServer",meta= (DisplayName = "Convert Struct To Json String", CustomStructureParam = "Struct", AutoCreateRefTerm = "Struct")
	static Json
	*/



	/*
	UFUNCTION(BlueprintCallable,Category = "HttpServer",meta= (DisplayName = "Convert Struct To Json String", CustomStructureParam = "Struct", AutoCreateRefTerm = "Struct"))
	static UPARAM(DisplayName="Success") bool Create_Http_ResponseData_Json2(int32 Code, FString Msg, const int32& Struct);
	DECLARE_FUNCTION(execCreate_Http_ResponseData_Json2);
	*/
	/*
	UFUNCTION(BlueprintCallable,Category = "HttpServer",meta= (DisplayName = "Convert Struct To Json String", CustomStructureParam = "Struct", AutoCreateRefTerm = "Struct"))
	static FString Serialize_Http_ResponseData(int32 Code, FString Msg, const UStruct* StructDefinition, const int32& Struct);
	DECLARE_FUNCTION(execSerialize_Http_ResponseData);
	*/
	
};
