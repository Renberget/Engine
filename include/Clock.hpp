#pragma once
#include <chrono>

class Clock
{
public:
	Clock();
	//Returns the elapsed time in seconds
	[[nodiscard]] float getSeconds() const;
	//Returns the elapsed time in milliseconds
	[[nodiscard]] int32_t getMilliseconds() const;
	//Returns the elapsed time in microseconds
	[[nodiscard]] int64_t getMicroseconds() const;
	//Restart the clock to 0
	void restart();

private:
	std::chrono::steady_clock::time_point mStart;
};
