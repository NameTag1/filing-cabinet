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
	sysFile.open("System Log.txt"); //Auto Clears Files
	actionFile.open("Action Log.txt"); //Auto Clears Files

	std::time_t now_c = std::time(nullptr);  // Faster than full chrono conversion
	std::tm* local_tm = std::localtime(&now_c);

	char timestring[80];
	std::strftime(timestring, sizeof(timestring), "%Y-%m-%d", local_tm);

	sysFile << timestring << "\n";
	actionFile << timestring << "\n";
}

void Logger::LogData(LogType l, std::string s)
{
	std::time_t now_c = std::time(nullptr);  // Faster than full chrono conversion
	std::tm* local_tm = std::localtime(&now_c);

	char timestring[80];
	std::strftime(timestring, sizeof(timestring), "%H:%M:%S", local_tm);

	std::string d = timestring;

	std::string i = d + " - " + s + "\n";
	logQueue.push_back(std::pair(l, i));

	/*switch (l) {
	case LogType::Sys:
		sysFile << timestring << " - " << s << "\n";
		break;
	case LogType::Action:
		actionFile << timestring << " - " << s << "\n";
		break;
	default:
		sysFile << timestring << " - " << "Incorrect Log Type!" << "\n";
	}*/
}

void Logger::WriteLog()
{
	for (auto i : logQueue) {
		switch (i.first) {
		case LogType::Sys:
			sysFile << i.second;
			break;
		case LogType::Action:
			actionFile << i.second;
			break;
		}
	}
}

void Logger::CloseLogger()
{
	sysFile.close();
	actionFile.close();
}
