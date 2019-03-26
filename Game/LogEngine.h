#pragma once

#include <iostream>
#include <string>

#include "Singleton.h"

#define LOG_TRACE 1
#define LOG_DEBUG 2
#define LOG_ERROR 4

//Static LogEngine class
class LogEngine
{
private:
	static LogEngine*	m_Instance;
    static std::string	m_SystemName;
	static int			m_FilterFlags;
	
	//Hidden constructor / destructor
	LogEngine();
	~LogEngine();
public:
	static int Init(int filterFlags);
	static void UnInit();
	static void Log(int flagsLogType, std::string strSystemName, std::string strMessage);

	//void Error(std::string strSystem, std::string strMessage);
	//void Trace(std::string strSystem, std::string strMessage);
	//void Trace(std::string strMessage);

	static void SetFilterFlags(int flags);

	//void AddFlag(int filterFlag);
	//void RemoveFlag(int filterFlag);
};


