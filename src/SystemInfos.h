#pragma once

#include <string>

class SystemInfos
{
public:
	std::string m_CommandLine;
	
public:
	void SetCommandLine(int* vArgc, char** vArgs);
	std::string GetInfosToJSON();
	
public: // singleton
	static SystemInfos* Instance()
	{
		static SystemInfos _instance;
		return &_instance;
	}
	SystemInfos() = default;
	SystemInfos(const SystemInfos&) = delete;
	SystemInfos& operator =(const SystemInfos&) = delete;
	~SystemInfos() = default;
};