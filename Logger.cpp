#include "pch.h"
#include "Logger.h"
#include <ctime>

std::ofstream Logger::s_stream;
std::mutex    Logger::s_mutex;

void Logger::Init(const std::string& logFile)
{
    std::lock_guard<std::mutex> lock(s_mutex);
    if (!s_stream.is_open())
    {
        s_stream.open(logFile, std::ios::out | std::ios::app);
    }
}

void Logger::Info(const std::string& msg)
{
    Write("INFO", msg);
}

void Logger::Error(const std::string& msg)
{
    Write("ERROR", msg);
}

void Logger::Write(const std::string& level, const std::string& msg)
{
    std::lock_guard<std::mutex> lock(s_mutex);
    if (!s_stream.is_open())
        return;

    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    s_stream << "[" << buf << "] "
        << "[" << level << "] "
        << msg << std::endl;
}
