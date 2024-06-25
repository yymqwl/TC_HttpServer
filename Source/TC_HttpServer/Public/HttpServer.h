// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpRequestHandler.h"
#include "HttpResponce_Controller.h"
#include "HttpResultCallback.h"
#include "GameFramework/Actor.h"
#include "HttpServer.generated.h"

//FHttpRequestHandler
//DECLARE_DELEGATE_RetVal_OneParam(FString,HttpRequstDelegate,FString);
//DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FString,FHttpRequst_Dynamic_Delegate,FString,InValue);
//DECLARE_DELEGATE()
//DECLEARE_DELEGATE();
UCLASS()
class TC_HTTPSERVER_API AHttpServer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHttpServer();

	void StartServer();
	void StopServer();

	TArray<UBlueprint*> GetAllBlueprints();

	void RegisterAll_Controller();
	
	/*
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Test();
	void Test_Implementation();
	*/
public:
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="HttpServer")
	int32 Port;
	
	//UPROPERTY(BlueprintReadWrite,Category="HttpServer")
	//FHttpRequst_Dynamic_Delegate Get_HttpRequst_Delegate;
protected:
	UPROPERTY(Transient)// (BlueprintReadWrite,EditAnywhere,Category="HttpServer")
	TMap<FString,TObjectPtr<UHttpResponce_Controller>> Get_HttpResponce_Controller_Map;
	UPROPERTY(Transient)//(BlueprintReadWrite,EditAnywhere,Category="HttpServer" ,meta = ( TitleProperty = "Http_Get"))
	TSet<TSubclassOf<UHttpResponce_Controller>> Http_Responce_Controller_Class;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	bool RequestGET(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);
	bool RequestPOST(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	bool IsServerStarted;
};
