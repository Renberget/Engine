#pragma once
#include "Buffer.hpp"
#include "Type.hpp"

class IndicesBuffer : public Buffer
{
public:
	IndicesBuffer() : Buffer(BufferType::IndicesArray, typeid(uint16_t)) {}
	template<typename T>
	IndicesBuffer(std::span<const T> indices, Usage usage) : Buffer(BufferType::IndicesArray)
	{
		create(indices, usage);
	}
	template<typename T, typename = std::enable_if_t<std::is_same_v<T, uint8_t> || std::is_same_v<T, uint16_t> || std::is_same_v<T, uint32_t>>>
	void create(std::span<const T> indices, Usage usage)
	{
		Buffer::create(indices, usage);
	}
	template<typename T>
	void update(std::span<const T> indices, size_t offset = 0)
	{
		Buffer::update(indices, offset);
	}
	template<typename T, Access A>
	RestrictedSpan<T, A> map()
	{
		return Buffer::map<T, A>();
	}
};
