#pragma once

#include "HttpData.generated.h"





//const FString

///请求HTTP返回数值
///Code 返回值
///Msg 额外消息
///Data 附带的JObject
///////////////////
USTRUCT(BlueprintType)
struct FHttp_ResponseData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName="返回码"));
	int32 Code;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(DisplayName="附带消息"));
	FString Msg;

	
	/*UFUNCTION(BlueprintCallable)
	FString Get_Data_Key() const
	{
		return FString("Data");
	}*/
	//FJsonValueObject Data;//这个是新添加的
};
