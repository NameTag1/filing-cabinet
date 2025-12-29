#pragma once

#include <thread>
#include <deque>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include <tesseract/baseapi.h>

class OCR_Wrapper
{
public:
	OCR_Wrapper();
	~OCR_Wrapper();

	void processScanQueue();
	void addToScanQueue(std::string filename);

	std::vector<std::string> scannedTexts;

private:
	std::thread* ocrThread;
	std::atomic<bool> threadRunning; //Used to signal thread to stop
	tesseract::TessBaseAPI* api;
	std::deque<std::string> scanQueue;

	// Synchronization for queue access and thread wake-up
	std::mutex queueMutex;
	std::condition_variable queueCv;
};

