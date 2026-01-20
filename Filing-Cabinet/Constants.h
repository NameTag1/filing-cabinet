#pragma once

#include "nlohmann/json.hpp"
using namespace nlohmann;

class Constants {
public:
	Constants(json Settings);

	static int TitleSize;
	static int SubtitleSize;
	static int NormaTextlSize;
};