#include "Logger.h"

#include <chrono>
#include <ctime>

Logger* Logger::Instance = new Logger();

Logger::Logger()
{
	Initialize();
}

void Logger::Initialize()
{
	sysFile.open("System Log.txt");
	actionFile.open("Action Log.txt");

	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::tm* local_tm = std::localtime(&now_c);

	char timestring[80];
	std::strftime(timestring, sizeof(timestring), "%Y-%m-%d", local_tm);
	
	sysFile << timestring << "\n";
	actionFile << timestring << "\n";
}

void Logger::LogData(LogType l, std::string s)
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::tm* local_tm = std::localtime(&now_c);

	char timestring[80];
	std::strftime(timestring, sizeof(timestring), "%H:%M:%S", local_tm);

	switch (l) {
	case LogType::Sys:
		sysFile << timestring << " - " << s << "\n";
		break;
	case LogType::Action:
		actionFile << timestring << " - " << s << "\n";
		break;
	default:
		sysFile << timestring << " - " << "Incorrect Log Type!" << "\n";
	}
}

void Logger::CloseLogger()
{
	sysFile.close();
	actionFile.close();
}
