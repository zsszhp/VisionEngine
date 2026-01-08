#pragma once
#include <string>
#include <fstream>
#include <mutex>

/**
 * @brief 简单企业级日志器
 */
class Logger
{
public:
    static void Init(const std::string& logFile);
    static void Info(const std::string& msg);
    static void Error(const std::string& msg);

private:
    static void Write(const std::string& level, const std::string& msg);

private:
    static std::ofstream s_stream;
    static std::mutex    s_mutex;
};
