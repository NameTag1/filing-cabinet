#include "OCR_Wrapper.h"

#include "Logger.h"
#include <leptonica/allheaders.h>
#include <thread>
#include <string>
#include <utility>
#include <mutex>

OCR_Wrapper::OCR_Wrapper()
	: ocrThread(nullptr)
	, threadRunning(false)
	, api(nullptr)
{
	api = new tesseract::TessBaseAPI();
	// NULL means use default datapath, CHANGE LATER
	if (api->Init(NULL, "eng")) {
		Logger::Instance->LogData(Logger::Sys, "OCR_Wrapper could not initialize API");
		// Do not start the thread if API failed to initialize.
		api->End();
		delete api;
		api = nullptr;
		threadRunning = false;
	}
	else {
		Logger::Instance->LogData(Logger::Sys, "OCR_Wrapper initialized API");
		threadRunning = true;
		ocrThread = new std::thread(&OCR_Wrapper::processScanQueue, this);
	}
}

OCR_Wrapper::~OCR_Wrapper()
{
	// Signal thread to stop and wake it if waiting
	threadRunning = false;
	queueCv.notify_all();

	if (ocrThread) {
		if (ocrThread->joinable()) {
			ocrThread->join();
		}
		delete ocrThread;
		ocrThread = nullptr;
	}

	// Closes API, freeing memory
	if (api) {
		api->End();
		delete api;
		api = nullptr;
	}
}

void OCR_Wrapper::processScanQueue()
{
	Logger::Instance->LogData(Logger::Sys, "OCR_Wrapper OCR Thread Started");

	while (threadRunning || !scanQueue.empty())
	{
		std::string filename;

		{
			std::unique_lock<std::mutex> lock(queueMutex);
			// Wait until there's work or we're shutting down
			queueCv.wait(lock, [this]() { return !threadRunning || !scanQueue.empty(); });

			if (!scanQueue.empty()) {
				// Pop front (FIFO)
				filename = std::move(scanQueue.front());
				scanQueue.pop_front();
			} else {
				// Nothing to do and threadStopping, loop will exit
				continue;
			}
		}

		// Load an image using Leptonica. c_str converts it to a char array
		Pix* image = pixRead(filename.c_str());
		if (!image) {
			Logger::Instance->LogData(Logger::Sys, "OCR_Wrapper could not load image " + filename);
			// continue processing remaining queue items
			continue;
		}

		// Set the image for OCR
		api->SetImage(image);

		// Perform OCR
		char* outText = api->GetUTF8Text();
		if (outText) {
			std::string result(outText);
			Logger::Instance->LogData(Logger::Action, "Scan Output:" + result);

			// Store result
			{
				std::lock_guard<std::mutex> lock(queueMutex);
				scannedTexts.push_back(std::move(result));
			}

			// Cleanup text buffer
			delete[] outText;
		} else {
			Logger::Instance->LogData(Logger::Sys, "OCR_Wrapper received null OCR output for " + filename);
		}

		// Cleanup image
		pixDestroy(&image);
	}

	Logger::Instance->LogData(Logger::Sys, "OCR_Wrapper OCR Thread Exiting");
}

void OCR_Wrapper::addToScanQueue(std::string filename)
{
	{
		std::lock_guard<std::mutex> lock(queueMutex);
		scanQueue.push_back(std::move(filename));
	}
	queueCv.notify_one();
}
