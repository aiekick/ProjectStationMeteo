#include "SystemInfos.h"
#include "MeasureDataBase.h"
#include "Build.h"

#ifdef UNIX
#include <sys/utsname.h>
#endif

void SystemInfos::SetCommandLine(int* vArgc, char** vArgs)
{
	m_CommandLine.clear();

	for (int i = 0; i < *vArgc; i++)
	{
		if (i)
			m_CommandLine += " ";
		m_CommandLine += vArgs[i];
	}
}

std::string SystemInfos::GetInfosToJSON()
{
	std::string json = "{";

	json += "\"server_version\" : \"" + std::string(BuildId) + "." + ((sizeof(size_t)==6)?"X64":"X32") + "\"" ;
	json += ",\"server_command\" : \"" + m_CommandLine + "\"";
	json += "," + MeasureDataBase::Instance()->GetDatabaseInfos();

	// os
#ifdef UNIX
/*	struct utsname
	{
		char sysname[];    // Operating system name (e.g., "Linux")
		char nodename[];   // Name within "some implementation-defined network"
		char release[];    // OS release (e.g., "2.6.28")
		char version[];    // OS version
		char machine[];    // Hardware identifier
#ifdef _GNU_SOURCE
		char domainname[]; // NIS or YP domain name
#endif
	}
*/
	struct utsname _utsName;
	if (uname(&_utsName) == 0)
	{
		json += ",\"os_sys_name\":\"" + std::string(_utsName.sysname) + "\"";
		//json += ",\"os_nodename\":\"" + std::string(_utsName.nodename) + "\"";, not necessary to export user name
		json += ",\"os_release\":\"" + std::string(_utsName.release) + "\"";
		json += ",\"os_version\":\"" + std::string(_utsName.version) + "\"";
		json += ",\"os_machine\":\"" + std::string(_utsName.machine) + "\"";
	}
#endif

	json += "}";

	return json;
}