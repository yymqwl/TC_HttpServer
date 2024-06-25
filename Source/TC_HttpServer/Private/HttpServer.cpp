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
	//GetAllBlueprints();
	StartServer();


	//GetAllDerivedClasses()
}

void AHttpServer::RegisterAll_Controller()
{
	Http_Responce_Controller_Class.Empty();
	
	auto all_classs =GetAllDerivedClasses();
	if (all_classs.Contains(UHttpResponce_Controller::StaticClass()) )
	{
		auto  hr_controller_class =all_classs[UHttpResponce_Controller::StaticClass()];
		for (auto controller_class : hr_controller_class)
		{
			Http_Responce_Controller_Class.Add(controller_class);
		}
	}
}

TArray<UBlueprint*> AHttpServer::GetAllBlueprints()
{
	HTTP_SERVER_LOG(TEXT("GetAllBlueprints") );
	TArray<UBlueprint*> Blueprints;
	// 获取所有加载的对象
	TArray<UObject*> AllObjects;

	
	GetObjectsOfClass(UHttpResponce_Controller::StaticClass(),AllObjects);
	//UObject::GetObjectsOfClass(UBlueprint::StaticClass(), AllObjects);
	 
	for (UObject* Object : AllObjects)
	{
		UBlueprint* BP = Cast<UBlueprint>(Object);
		HTTP_SERVER_LOG(TEXT("%s"),*BP->ParentClass->GetName() );
		if (BP && BP->GeneratedClass && BP->GeneratedClass->ClassGeneratedBy)
		{
			Blueprints.Add(BP);
		}
	}
 
	return Blueprints;
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
		Get_HttpResponce_Controller_Map.Empty();
		RegisterAll_Controller();
		
		for (auto hrc : Http_Responce_Controller_Class)
		{
			auto hr = Cast<UHttpResponce_Controller>(hrc.GetDefaultObject());
			//HTTP_SERVER_LOG(TEXT("%s"),*hr->GetName());
			if (Get_HttpResponce_Controller_Map.Contains(hr->HttpPath))
			{
				HTTP_SERVER_ERROR(TEXT("Same HttpPath:%s"),*hr->HttpPath);
			}
			else if (hr->HttpPath.IsEmpty())
			{
				HTTP_SERVER_LOG(TEXT("HttpPath Null:%s"),*hr->HttpPath);
			}
			else
			{
				Get_HttpResponce_Controller_Map.Add(hr->HttpPath, hr);
			}
		}
		
		for (auto kv : Get_HttpResponce_Controller_Map)
		{
			const FHttpRequestHandler RequestHandler = FHttpRequestHandler::CreateLambda([this, kv]
			(const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)
			{
				//FJsonObjectConverter
				//HTTP_SERVER_LOG(TEXT("线程Id为%d,是否游戏线程%d"),FPlatformTLS::GetCurrentThreadId(),IsInGameThread());
				FString res = kv.Value->Parse(Request.QueryParams);
				TUniquePtr<FHttpServerResponse> response = FHttpServerResponse::Create(res, TEXT("text/html"));
				OnComplete(MoveTemp(response));
				return true;
			});
			if (kv.Value->HttpType == EHttpType::Get)
			{
				FHttpRouteHandle HttpRouteHandle = httpRouter->BindRoute(kv.Key,EHttpServerRequestVerbs::VERB_GET,RequestHandler);
			}
			else if(kv.Value->HttpType == EHttpType::Post)
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
