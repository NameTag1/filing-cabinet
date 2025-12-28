#pragma once
#include <string>
#include <fstream>
#include <vector>

class Logger
{
public:
	enum LogType {
		Sys,
		Action
	};
	static Logger* Instance;

	Logger();
	void Initialize();
	void LogData(LogType l, std::string s);
	void WriteLog();
	void CloseLogger();

	// Install handlers to try to capture crashes and flush logs
	static void InstallCrashHandlers();

private:
	std::vector<std::pair<LogType, std::string>> logQueue;
	std::ofstream sysFile;
	std::ofstream actionFile;
};

