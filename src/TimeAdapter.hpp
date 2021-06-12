#ifndef TIMEADAPTER_H
#define TIMEADAPTER_H

#include <chrono> 
#include <time.h>
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string> 
#include "Interfaces/NonCopyable.hpp" 
	
class TimeAdapter : public NonCopyable  
{
private:
	TimeAdapter()=delete;
	~TimeAdapter()=delete;
public:
	static std::chrono::microseconds timevalToDuration(struct timeval timeStamp);
	static std::chrono::system_clock::time_point timevalToTimePoint(struct timeval timeStamp); 
	static std::string toString(const std::chrono::system_clock::time_point timeStamp);
};
#endif