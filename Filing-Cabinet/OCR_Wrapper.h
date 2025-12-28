#pragma once

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

class OCR_Wrapper
{
public:
	OCR_Wrapper();
	~OCR_Wrapper();
	void getText(std::string filename);

private:
	tesseract::TessBaseAPI* api;
};

