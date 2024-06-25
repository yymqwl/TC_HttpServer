#pragma once
#include "HttpServerLog.h"

class FMapHelper
{
public:

	//template< typename T >
	static FString Get_Key_DefaultValue(const TMap<FString,FString>& map,const FString& key,const FString& default_string)
	{
		if (map.Contains(key))
		{
			return  map[key];
			/*{
				HTTP_SERVER_LOG(TEXT("Get_Key_DefaultValue %s 没有转换类型"),*key)
			}*/
		}
		return default_string;
	}
	
};
