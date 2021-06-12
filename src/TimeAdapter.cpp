#include "TimeAdapter.hpp"  

std::chrono::microseconds TimeAdapter::timevalToDuration(struct timeval timeStamp)
{
    auto duration = std::chrono::seconds{timeStamp.tv_sec} + std::chrono::microseconds{timeStamp.tv_usec};
    return std::chrono::duration_cast<std::chrono::microseconds>(duration);
}

std::chrono::system_clock::time_point TimeAdapter::timevalToTimePoint(struct timeval timeStamp)
{
    return std::chrono::system_clock::time_point{timevalToDuration(timeStamp)};
}

std::string TimeAdapter::toString(const std::chrono::system_clock::time_point timeStamp)
{
    std::stringstream ss;
    auto time = std::chrono::system_clock::to_time_t(timeStamp);
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}	