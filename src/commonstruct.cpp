
#include "commonstruct.h"
#include "Ini.h"

T_CONFFILE	g_confFile;

CCommonStruct::CCommonStruct()
{
}

CCommonStruct::~CCommonStruct()
{
}


string GUIDToString(T_GUID guid)
{
    char buf[100];
    sprintf( buf, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1],
        guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5],
        guid.Data4[6], guid.Data4[7]);
    return string(buf);
}

T_GUID StringToGUID(const char *str)
{
    int t1,t2,t3,t4;
    T_GUID guid;
    sscanf(str,
        "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
        &guid.Data1, &guid.Data2, &guid.Data3,
        &guid.Data4[0],&guid.Data4[1],
        &guid.Data4[2],&guid.Data4[3],
        &t1, &t2,
        &t3, &t4);

    guid.Data4[4] = t1;
    guid.Data4[5] = t2;
    guid.Data4[6] = t3;
    guid.Data4[7] = t4;
    return guid;
}


bool CCommonStruct::ReadConfig(const char* acpszConfigFilePath)
{
	CIniFile iniFile;
	bool bRtn = iniFile.open(acpszConfigFilePath);
	if(!bRtn)
		return false;


	char			pszConfSvrIP[AVM_MAX_IP_LEN];
	unsigned int    uiConfSvrIP;
	unsigned short	usConfSvrPort;
	string			strLogDir;

	string strTemp("");
	strTemp = iniFile.read("confsvr", "ip");
	if(strTemp.empty())	
		strcpy(g_confFile.pszConfSvrIP, "0.0.0.0");
	else
		strcpy(g_confFile.pszConfSvrIP, strTemp.c_str());

	strTemp = iniFile.read("confsvr", "port");
	if(strTemp.empty())
		g_confFile.usConfSvrPort = 4879;
	else
		g_confFile.usConfSvrPort = atoi(strTemp.c_str());

	strTemp = iniFile.read("local", "logdir");
	if(strTemp.empty())	
        g_confFile.strLogDir = "/var/log";
	else
        g_confFile.strLogDir=strTemp;
	
	strTemp = iniFile.read("local", "name");
	if(strTemp.empty())	
        g_confFile.strName = "CCNBJDefault01";
	else
        g_confFile.strName=strTemp;

	strTemp = iniFile.read("local", "type");
	if(strTemp.empty())	
        g_confFile.strType = "avcodec";
	else
        g_confFile.strType=strTemp;

	strTemp = iniFile.read("local", "maxroom");
	if(strTemp.empty())
		g_confFile.iMaxRoom = 200;
	else
		g_confFile.iMaxRoom = atoi(strTemp.c_str());

	return true;
}

char* CCommonStruct::Time2String(time_t time1)
{
	static char szTime[1024]="";
	memset(szTime, 0, 1024);
	struct tm tm1;  
    localtime_r(&time1, &tm1 );  
	sprintf( szTime, "%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d",  
	               tm1.tm_year+1900, tm1.tm_mon+1, tm1.tm_mday,  
	               tm1.tm_hour, tm1.tm_min,tm1.tm_sec);  
	return szTime;
}


