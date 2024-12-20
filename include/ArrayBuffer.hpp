#pragma once
#include "Buffer.hpp"

class ArrayBuffer : public Buffer
{
public:
	ArrayBuffer() : Buffer() {}
	template<typename T>
	void create(size_t size, Flags<BufferFlags> flags = {})
	{
		Buffer::create<T>(size, flags);
	}
	template<typename T>
	void create(std::initializer_list<T> data, Flags<BufferFlags> flags = {})
	{
		Buffer::create(data, flags);
	}
	template<typename T>
	void create(std::span<const T> data, Flags<BufferFlags> flags = {})
	{
		Buffer::create(data, flags);
	}
	template<typename T>
	void update(std::initializer_list<T> data, size_t offset = 0)
	{
		Buffer::update(data, offset);
	}
	template<typename T>
	void update(std::span<const T> data, size_t offset = 0)
	{
		Buffer::update(data, offset);
	}
	template<typename T, Access A>
	RestrictedSpan<T, A> map()
	{
		return Buffer::map<T, A>();
	}
};
