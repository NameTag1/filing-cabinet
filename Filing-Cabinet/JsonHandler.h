#pragma once

#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "Logger.h"

class JsonHandler
{
public:
	JsonHandler();
	void setLogger(Logger* l);
	void openJson(std::string accessKey, std::string filePath);
	void writeAll();
	void clearEntry(std::string accessKey);
	void closeAll();

	std::map<std::string, json> DATA;
private:
	std::map<std::string, std::string> accessKeyToFile;
	Logger* logger;
};

