#include "OCR_Wrapper.h"

#include "Logger.h"

OCR_Wrapper::OCR_Wrapper()
{
	api = new tesseract::TessBaseAPI();
	//NULL means use default datapath, CHANGE LATER
    if (api->Init(NULL, "eng")) {
        Logger::Instance->LogData(Logger::Sys, "OCR_Wrapper could not initialize API");
        return;
    }
    else {
        Logger::Instance->LogData(Logger::Sys, "OCR_Wrapper initialized API");
    }
}

OCR_Wrapper::~OCR_Wrapper()
{
	//Closes API, freeing memory
    api->End();
}

void OCR_Wrapper::getText(std::string filename)
{
    // Load an image using Leptonica. c_str converts it to a char array
    Pix* image = pixRead(filename.c_str());
    if (!image) {
        Logger::Instance->LogData(Logger::Sys, "OCR_Wrapper could not load image " + filename);
        return;
    }

    // Set the image for OCR
    api->SetImage(image);

    // Perform OCR
    char* outText = api->GetUTF8Text();

    Logger::Instance->LogData(Logger::Action, "Scan Output:" + std::string(outText));

    // Cleanup
    delete[] outText;
    pixDestroy(&image);
}
