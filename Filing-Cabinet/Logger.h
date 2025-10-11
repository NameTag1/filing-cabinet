#pragma once
#include <string>
#include <fstream>

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
	void CloseLogger();

private:
	std::ofstream sysFile;
	std::ofstream actionFile;
};

