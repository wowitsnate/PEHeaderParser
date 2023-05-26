#pragma once

enum class LogType : int
{
    Info,
    Warning,
    Error
};

enum class DateTimeType : int
{
    Time,
    Date,
    DateTime
};

class Logger {
    //Class to handle logging of errors and info, with varying level and store in a txt file;
private:
    std::mutex FileWriteLock;
    DateTimeType Format;
    std::ofstream LogFile;

private:
    std::string GetDateTimeFormatted(DateTimeType dt);

public:
    Logger(const std::string&, DateTimeType);
    ~Logger();
    bool WriteLog(const std::string&, const LogType);
};