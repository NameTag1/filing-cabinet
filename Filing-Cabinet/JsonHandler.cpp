#include "JsonHandler.h"

#include <fstream>

JsonHandler::JsonHandler()
{
}

void JsonHandler::setLogger(Logger* l)
{
	logger = l;
}

void JsonHandler::openJson(std::string accessKey, std::string filePath)
{
	std::ifstream JsonFileWrapper(filePath);
	if (!JsonFileWrapper) {
		logger->LogData(Logger::Action, "JsonHandler failed to open " + filePath);
		return;
	}
	else {
		logger->LogData(Logger::Action, "JsonHandler opened " + filePath);
	}
	accessKeyToFile[accessKey] = filePath;
	DATA[accessKey] = *(new json()); //Initialize JSON object
	JsonFileWrapper >> DATA[accessKey]; //Put data into JSON object
	JsonFileWrapper.close();
}

void JsonHandler::writeAll()
{
	for (auto& i : DATA) {
		std::ofstream o(accessKeyToFile[i.first]); //Opens file to output into
		o << i.second.dump(4); //Json object dumped into output file
	}
}

void JsonHandler::clearEntry(std::string accessKey)
{
}

void JsonHandler::closeAll()
{
	DATA.clear();
}
