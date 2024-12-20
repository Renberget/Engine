#pragma once
#include "BlockBuffer.hpp"

class ShaderStorageBuffer : public BlockBuffer
{
public:
	ShaderStorageBuffer();
	template<typename T, auto T::*... Members>
	void create(size_t size, Flags<BufferFlags> flags = {})
	{
		BlockBuffer::create<T, Members...>(size, flags);
		create();
	}
	template<typename T, auto T::*... Members>
	void create(std::initializer_list<T> data, Flags<BufferFlags> flags = {})
	{
		BlockBuffer::create<T, Members...>(data, flags);
		create();
	}
	template<typename T, auto T::*... Members>
	void create(std::span<const T> data, Flags<BufferFlags> flags = {})
	{
		BlockBuffer::create<T, Members...>(data, flags);
		create();
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
	//Returns the OpenGL binding
	[[nodiscard]] Binding binding() const;

private:
	constexpr static Binding InvalidBinding = -1;
	static Binding sCurrentBinding;

	void create();

	Binding mBinding = InvalidBinding;
};