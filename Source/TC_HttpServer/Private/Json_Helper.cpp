#include "Json_Helper.h"

#include "HttpData.h"
#include "HttpServer_GameConstant.h"
#include "HttpServerLog.h"
#include "JsonObjectConverter.h"
#include "Blueprint/BlueprintExceptionInfo.h"

#define LOCTEXT_NAMESPACE "UJson_Helper"




FJsonObjectWrapper UJson_Helper::Create_Http_ResponseData_Json(int32 Code,FString Msg)
{
	FJsonObjectWrapper jow;
	FHttp_ResponseData http_response_data {Code,Msg};
	jow.JsonObject = FJsonObjectConverter::UStructToJsonObject<FHttp_ResponseData>(http_response_data);
	return jow;
}
/*
FJsonObjectWrapper UJson_Helper::Create_Http_ResponseData_Json2(int32 Code, FString Msg, const int32& Struct)
{
	FJsonObjectWrapper jow;
	FHttp_ResponseData http_response_data {Code,Msg};
	jow.JsonObject = FJsonObjectConverter::UStructToJsonObject<FHttp_ResponseData>(http_response_data);

	
	return jow;
}*/

/*
DEFINE_FUNCTION(UJson_Helper::execCreate_Http_ResponseData_Json2)
{
	//P_GET_STRUCT_REF(FStructProperty, Struct);
	//P_GET_PROPERTY(FIntProperty, Code);
	//P_GET_PROPERTY(FStrProperty, Msg);
	
	Stack.StepCompiledIn<FProperty>(nullptr);
	FProperty* ValueProperty = Stack.MostRecentProperty;
	void* ValuePtr = Stack.MostRecentPropertyAddress;

	PARAM_PASSED_BY_REF(OutJsonString, FStrProperty, FString);

	P_FINISH;

	if (!ValueProperty || !ValuePtr)
	{
		const FBlueprintExceptionInfo ExceptionInfo(
			EBlueprintExceptionType::AccessViolation,
			LOCTEXT("StructToJsonString_MissingInputProperty", "Failed to resolve the input parameter for StructToJsonString.")
		);
		FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
	}

	bool bResult;
	FStructProperty* const StructProperty = CastField<FStructProperty>(ValueProperty);
	if (!StructProperty)
	{
		bResult = false;
		*StaticCast<bool*>(RESULT_PARAM) = bResult;
		return;
	}
	
	P_NATIVE_BEGIN
	bResult = FJsonObjectConverter::UStructToJsonObjectString(StructProperty->Struct, ValuePtr, OutJsonString);
	P_NATIVE_END

	*StaticCast<bool*>(RESULT_PARAM) = bResult;
}*/
/*
FString UJson_Helper::Serialize_Http_ResponseData(int32 Code,FString Msg,const UStruct* StructDefinition,const int32& Struct)
{
	
	
	//UStruct* StructDefinition = nullptr;
	//const void* Struct = nullptr;
	
	FString OutputString ;
	//auto jsonObject_Data = MakeShared<FJsonObject>();
	FHttp_ResponseData http_response_data {Code,Msg};
	TSharedPtr<FJsonObject> jo_h_rd = FJsonObjectConverter::UStructToJsonObject<FHttp_ResponseData>(http_response_data);
	
	
	auto jo_data = MakeShared<FJsonObject>();
	if (!FJsonObjectConverter::UStructToJsonObject(StructDefinition,&Struct,jo_data))
	{
		HTTP_SERVER_ERROR(TEXT("Json_Helper_结构体转换错误 "));
		return  OutputString;
	}
	
	jo_h_rd->SetObjectField(UHttpServer_GameConstant::Get_Json_Key_Data(),jo_data);

	
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
    FJsonSerializer::Serialize(jo_h_rd.ToSharedRef(), Writer);

	return OutputString;
	
	
}*/


#undef LOCTEXT_NAMESPACE