#pragma once
#include "Buffer.hpp"
#include "Type.hpp"


template<typename T>
concept buffer_index = std::is_same_v<T, uint8_t> || std::is_same_v<T, uint16_t> || std::is_same_v<T, uint32_t>;

class IndicesBuffer : public Buffer
{
public:
	IndicesBuffer() : Buffer() {}
	template<buffer_index T>
	void create(size_t size, Flags<BufferFlags> flags = {})
	{
		Buffer::create<T>(size, flags);
	}
	template<buffer_index T>
	void create(std::initializer_list<T> indices, Flags<BufferFlags> flags = {})
	{
		Buffer::create(indices, flags);
	}
	template<buffer_index T>
	void create(std::span<const T> indices, Flags<BufferFlags> flags = {})
	{
		Buffer::create(indices, flags);
	}
	template<buffer_index T>
	void update(std::initializer_list<T> indices, size_t offset = 0)
	{
		Buffer::update(indices, offset);
	}
	template<buffer_index T>
	void update(std::span<const T> indices, size_t offset = 0)
	{
		Buffer::update(indices, offset);
	}
	template<buffer_index T, Access A>
	RestrictedSpan<T, A> map()
	{
		return Buffer::map<T, A>();
	}
};
