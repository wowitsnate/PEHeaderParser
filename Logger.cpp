#pragma once
#pragma warning (disable : 4996)

#include "includes.h"


std::string Logger::GetDateTimeFormatted(DateTimeType dt) {
    time_t curTime = time(NULL);
    struct tm tstruct;
    char buffer[80];
    tstruct = *(localtime(&curTime));

    switch (dt) {
    case DateTimeType::Time:
        strftime(buffer, sizeof(buffer), "[%X]", &tstruct);
        break;

    case DateTimeType::Date:
        strftime(buffer, sizeof(buffer), "[%Y-%m-%d]", &tstruct);
        break;

    case DateTimeType::DateTime:
        strftime(buffer, sizeof(buffer), "[%Y-%m-%d %X]", &tstruct);
        break;

    default:
        return "[TIME FORMAT ERROR]";
        break;
    }
    return std::string(buffer);
}

Logger::Logger(const std::string& FilePath, DateTimeType _format) {
    Format = _format;
    LogFile.open(FilePath);

    if (!LogFile.is_open())
        std::runtime_error("Logging Failed: Filepath Not Found");

    WriteLog("Debug Log Initialized", LogType::Info);
}

Logger::~Logger() {
    LogFile.close();
}

bool Logger::WriteLog(const std::string& DBGMessage, const LogType Type) {
    std::string FormatPrefix;
    switch (Type) {
    case LogType::Info:
        FormatPrefix = "[INFO]";
        break;

    case LogType::Warning:
        FormatPrefix = "[WARNING]";
        break;

    case LogType::Error:
        FormatPrefix = "[ERROR]";
        break;

    default:
        return false;
    }

    FileWriteLock.lock();
    LogFile << FormatPrefix + GetDateTimeFormatted(Format) + ": " + DBGMessage << std::endl;
    FileWriteLock.unlock();
    return true;
}
