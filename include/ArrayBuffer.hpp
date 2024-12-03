#pragma once
#include "Buffer.hpp"

class ArrayBuffer : public Buffer
{
public:
	ArrayBuffer() : Buffer(BufferType::Array) {}
	template<StandardLayout T>
	ArrayBuffer(std::span<const T> data, Usage usage) : Buffer(BufferType::Array)
	{
		create(data, usage);
	}
	template<StandardLayout T>
	void create(std::span<const T> data, Usage usage)
	{
		Buffer::create(data, usage);
	}
	template<StandardLayout T>
	void update(std::span<const T> data, size_t offset = 0)
	{
		Buffer::update(data, offset);
	}
	template<StandardLayout T, Access A>
	RestrictedSpan<T, A> map()
	{
		return Buffer::map<T, A>();
	}
};
