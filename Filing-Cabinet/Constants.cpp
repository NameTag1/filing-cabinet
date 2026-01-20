#include "Constants.h"

int Constants::TitleSize = 36;
int Constants::SubtitleSize = 24;
int Constants::NormaTextlSize = 12;

Constants::Constants(json Settings)
{
	TitleSize = Settings["Text"]["TitleSize"];
	SubtitleSize = Settings["Text"]["SubtitleSize"];
	NormaTextlSize = Settings["Text"]["NormaTextlSize"];
}
