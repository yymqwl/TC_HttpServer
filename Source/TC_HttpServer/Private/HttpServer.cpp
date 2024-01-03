// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpServer.h"

#include "HttpServerLog.h"
#include "HttpServerModule.h"
#include "IHttpRouter.h"


// Sets default values
AHttpServer::AHttpServer():IsServerStarted(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHttpServer::BeginPlay()
{
	Super::BeginPlay();
	StartServer();
}
void AHttpServer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	StopServer();
}
void AHttpServer::StopServer()
{
	if (!IsServerStarted)
	{
		return;
	}
	
	FHttpServerModule& httpServerModule = FHttpServerModule::Get();
	httpServerModule.StartAllListeners();
}


void AHttpServer::StartServer()
{
	if (IsServerStarted)
	{
		HTTP_SERVER_LOG(TEXT("HttpServer already started"));
		return;
	}
	if (Port <= 0)
	{
		HTTP_SERVER_ERROR(TEXT("Could not start HttpServer, port number must be greater than zero! %d"),Port);
		return;
	}
	FHttpServerModule& httpServerModule = FHttpServerModule::Get();
	TSharedPtr<IHttpRouter> httpRouter = httpServerModule.GetHttpRouter(Port);

	
	//Http_Responce->Psrse()
	
	//GEngine->add
	//bind port
	//
	if (httpRouter.IsValid())
	{
		Get_HttpResponce_Map.Empty();
		for (auto hrc : Http_Responce_Class)
		{
			auto hr = Cast<UHttpResponce>(hrc.GetDefaultObject());
			//HTTP_SERVER_LOG(TEXT("%s"),*hr->GetName());
			if (Get_HttpResponce_Map.Contains(hr->HttpPath))
			{
				HTTP_SERVER_ERROR(TEXT("Same HttpPath:%s"),*hr->HttpPath);
			}
			else
			{
				Get_HttpResponce_Map.Add(hr->HttpPath, hr);
			}
		}
		
		for (auto kv : Get_HttpResponce_Map)
		{
			const FHttpRequestHandler RequestHandler = [this,kv]
			(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)
			{
				FString res = kv.Value->Parse(Request.QueryParams);
				TUniquePtr<FHttpServerResponse> response = FHttpServerResponse::Create(res,TEXT("text/html"));
				OnComplete(MoveTemp(response));
				return true;
			};
			if (kv.Value->HttpType == EHttpType::Get)
			{
				FHttpRouteHandle HttpRouteHandle = httpRouter->BindRoute(kv.Key,EHttpServerRequestVerbs::VERB_GET,RequestHandler);
			}
			else
			{
				FHttpRouteHandle HttpRouteHandle = httpRouter->BindRoute(kv.Key,EHttpServerRequestVerbs::VERB_POST,RequestHandler);
			}
		}
		FHttpServerModule::Get().StartAllListeners();
		IsServerStarted=true;
		
	}
	else
	{
		HTTP_SERVER_ERROR(TEXT("Could Not Start HttpServer HttpRouter"));
		IsServerStarted = false;
	}

	
}


// Called every frame
void AHttpServer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
void AHttpServer::Test_Implementation()
{
	HTTP_SERVER_LOG(TEXT("Test_Implementation "));
}*/
