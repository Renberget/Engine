#pragma once
#include "BlockBuffer.hpp"

class UniformBuffer : public BlockBuffer
{
public:
	UniformBuffer();
	//The used object layout must match the shader's one
	template<typename T, auto T::*... Members>
	void create(size_t size, Flags<BufferFlags> flags = {})
	{
		BlockBuffer::create<T, Members...>(size, flags);
		create();
	}
	//The used object layout must match the shader's one
	template<typename T, auto T::*... Members>
	void create(const T& data, Flags<BufferFlags> flags = {})
	{
		BlockBuffer::create<T, Members...>(std::span(&data, 1), flags);
		create();
	}
	template<typename T>
	void update(const T& data)
	{
		Buffer::update(std::span(&data, 1), 0);
	}
	template<typename T, auto T::* Member>
	void update(const member_ptr_to_type_t<decltype(Member)>& data)
	{
		Buffer::update(Span(&data, 1), member_offset<T, Member>());
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
