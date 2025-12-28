#include "Logger.h"

#include <chrono>
#include <ctime>
#include <csignal>
#include <exception>
#include <cstdlib>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

Logger* Logger::Instance = new Logger();

static void terminateHandler()
{
    try {
        // try to rethrow the current exception to get information
        auto ep = std::current_exception();
        if (ep) std::rethrow_exception(ep);
    }
    catch (const std::exception& e) {
        if (Logger::Instance)
            Logger::Instance->LogData(Logger::Sys, std::string("Unhandled exception: ") + e.what());
    }
    catch (...) {
        if (Logger::Instance)
            Logger::Instance->LogData(Logger::Sys, "Unhandled non-std exception");
    }

    if (Logger::Instance) {
        Logger::Instance->CloseLogger();
    }

    std::abort(); // re-raise fatal
}

static void signalHandler(int sig)
{
    if (Logger::Instance) {
        Logger::Instance->LogData(Logger::Sys, std::string("Fatal signal received: ") + std::to_string(sig));
        // Close/flush logs. Note: calling complex functions from a signal handler is not strictly safe.
        Logger::Instance->CloseLogger();
    }
    // _Exit avoids invoking further C++ cleanup which might be unsafe in this state
#if defined(_WIN32)
    ::ExitProcess(1);
#else
    _Exit(1);
#endif
}

#ifdef _WIN32
static LONG WINAPI sehHandler(EXCEPTION_POINTERS* ep)
{
    if (Logger::Instance) {
        std::string msg = "Unhandled SEH exception code: " + std::to_string(static_cast<unsigned long>(ep->ExceptionRecord->ExceptionCode));
        Logger::Instance->LogData(Logger::Sys, msg);
        Logger::Instance->CloseLogger();
    }
    return EXCEPTION_EXECUTE_HANDLER;
}
#endif

Logger::Logger()
{
    Initialize();
}

void Logger::Initialize()
{
    sysFile.open("System Log.txt"); //Auto Clears Files
    actionFile.open("Action Log.txt"); //Auto Clears Files

    std::time_t now_c = std::time(nullptr);  // Faster than full chrono conversion
    std::tm* local_tm = std::localtime(&now_c);

    char timestring[80];
    std::strftime(timestring, sizeof(timestring), "%Y-%m-%d", local_tm);

    sysFile << timestring << "\n";
    actionFile << timestring << "\n";

    Logger::Instance = this;

    // install crash handlers
    InstallCrashHandlers();

    // ensure CloseLogger is called on normal exit
    std::atexit([]() { if (Logger::Instance) Logger::Instance->CloseLogger(); });
}

void Logger::LogData(LogType l, std::string s)
{
    std::time_t now_c = std::time(nullptr);  // Faster than full chrono conversion
    std::tm* local_tm = std::localtime(&now_c);

    char timestring[80];
    std::strftime(timestring, sizeof(timestring), "%H:%M:%S", local_tm);

    std::string d = timestring;

    std::string i = d + " - " + s + "\n";
    logQueue.push_back(std::pair<Logger::LogType, std::string>(l, i));

    switch (l) {
    case LogType::Sys:
        sysFile << timestring << " - " << s << "\n";
        // flush immediately so data is written to disk even on crash
        sysFile.flush();
        break;
    case LogType::Action:
        actionFile << timestring << " - " << s << "\n";
        actionFile.flush();
        break;
    default:
        sysFile << timestring << " - " << "Incorrect Log Type!" << "\n";
        sysFile.flush();
    }
}

void Logger::WriteLog()
{
    /*for (auto i : logQueue) {
        switch (i.first) {
        case LogType::Sys:
            sysFile << i.second;
            break;
        case LogType::Action:
            actionFile << i.second;
            break;
        }
    }*/
}

void Logger::CloseLogger()
{
    // flush queued data and close files
    try {
        if (sysFile.is_open()) {
            sysFile.flush();
            sysFile.close();
        }
        if (actionFile.is_open()) {
            actionFile.flush();
            actionFile.close();
        }
    }
    catch (...) {
        // don't throw from destructor / close path
    }
}

void Logger::InstallCrashHandlers()
{
    // C++ terminate handler for uncaught exceptions
    std::set_terminate(terminateHandler);

    // POSIX / C signals (best-effort)
    std::signal(SIGABRT, signalHandler);
    std::signal(SIGILL, signalHandler);
    std::signal(SIGFPE, signalHandler);
    std::signal(SIGSEGV, signalHandler);
    std::signal(SIGTERM, signalHandler);

#ifdef _WIN32
    // Windows Structured Exception Handling (SEH) handler
    SetUnhandledExceptionFilter(sehHandler);
#endif
}
