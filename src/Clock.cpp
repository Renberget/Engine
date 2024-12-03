#include "Clock.hpp"

using namespace std::chrono;

Clock::Clock()
{
	mStart = steady_clock::now();
}

float Clock::getSeconds() const
{
	return duration<float>(steady_clock::now() - mStart).count();
}

int32_t Clock::getMilliseconds() const
{
	return duration_cast<duration<int32_t, std::milli>>(steady_clock::now() - mStart).count();
}

int64_t Clock::getMicroseconds() const
{
	return duration_cast<microseconds>(steady_clock::now() - mStart).count();
}

void Clock::restart()
{
	mStart = steady_clock::now();
}