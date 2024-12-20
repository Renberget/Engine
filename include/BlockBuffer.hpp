#pragma once
#include "Buffer.hpp"
#include "Utils/Meta.hpp"
#include <vector>
#include <stdexcept>

class BlockBuffer : public Buffer
{
public:
	using Binding = uint32_t;
	
	template<typename T, auto T::*... Members>
	void create(size_t size, Flags<BufferFlags> flags)
	{
		if (!Buffer::id())
			registerOffsets<T, Members...>();
		Buffer::create(size, flags);
	}
	template<typename T, auto T::*... Members>
	void create(std::initializer_list<T> data, Flags<BufferFlags> flags)
	{
		if (!Buffer::id())
			registerOffsets<T, Members...>();
		Buffer::create(data, flags);
	}
	template<typename T, auto T::*... Members>
	void create(std::span<const T> data, Flags<BufferFlags> flags)
	{
		if (!Buffer::id())
			registerOffsets<T, Members...>();
		Buffer::create(data, flags);
	}

protected:
	BlockBuffer() : Buffer() {}

#ifndef NDEBUG //Used in shader for debugging
public:
	[[nodiscard]] const std::vector<size_t>& layout() const
	{
		return mLayout;
	}

private:
	std::vector<size_t> mLayout;

	template<typename T, auto T::*... Members>
	void registerOffsets()
	{
		//Check if the members of T are ordered correctly and get their offsets
		size_t currentOffset = 0;
		([&]
			{
				size_t memberOffset = member_offset<T, Members>;
				if (memberOffset < currentOffset)
					throw std::runtime_error("Object members are not ordered correctly");
				currentOffset = memberOffset;
				mLayout.push_back(currentOffset);
			}(), ...);
	}
#endif
};