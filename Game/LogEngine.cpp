#include "LogEngine.h"

LogEngine* LogEngine::m_Instance = nullptr;
std::string	LogEngine::m_SystemName = "LogEngine";
int	LogEngine::m_FilterFlags;

//Hidden Constructor - won't be called - since it's static (no instantiation)
LogEngine::LogEngine()
{
	Log(LOG_TRACE, m_SystemName, "Constructor called.");
}

//Hidden Desctructor - won't be called - since it's static (no instantiation)
LogEngine::~LogEngine()
{
	Log(LOG_TRACE, m_SystemName, "Destructor called.");
}

//PUBLIC
int LogEngine::Init(int filterFlags)
{
	//Log GameEngine Init without LogEngine
	m_SystemName = "LogEngine";
	m_FilterFlags = filterFlags;

	Log(LOG_TRACE, m_SystemName, "Init() called.");
	
	//Log init was OK;
	LogEngine::Log(LOG_TRACE, m_SystemName, "Init()...OK.");

	return 0;
}

void LogEngine::UnInit()
{
	LogEngine::Log(LOG_TRACE, m_SystemName, "UnInit...OK.");
}

void LogEngine::Log(int flagsLogType, std::string strSystemName, std::string strMessage)
{
	if (m_FilterFlags & flagsLogType)
	{
		if (flagsLogType == LOG_TRACE) std::cout << "[TRACE] - ";
		if (flagsLogType == LOG_DEBUG) std::cout << "[DEBUG] - ";
		if (flagsLogType == LOG_ERROR) std::cout << "[ERROR] - ";
		
		if (strSystemName != "") std::cout << strSystemName << ": ";
		std::cout << strMessage << std::endl;
	}
}

/*
void LogEngine::Error(std::string strSystemName, std::string strMessage)
{
	std::cerr << "[ERROR] - ";
	if (strSystemName != "") std::cerr << strSystemName << ": ";
	std::cerr << strMessage << std::endl;
}

void LogEngine::Trace(std::string strSystemName, std::string strMessage)
{
	std::cout << "[TRACE] - ";
	if (strSystemName != "") std::cout << strSystemName << ": ";
	std::cout << strMessage << std::endl;
}

void LogEngine::Trace(std::string strMessage)
{
	std::cout << strMessage << std::endl;
}
*/

void LogEngine::SetFilterFlags(int filterFlags)
{
	m_FilterFlags = filterFlags;
}