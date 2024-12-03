#pragma once
#include "Buffer.hpp"
#include "Utils/MoreTypeTraits.hpp"

class UniformBuffer : public Buffer
{
public:
	UniformBuffer();
	//Used struct must respect the OpenGL's std140 memory layout
	template<StandardLayout T>
	explicit UniformBuffer(const T& data, Usage usage) : Buffer(BufferType::Uniform)
	{
		create(data, usage);
	}
	template<StandardLayout T>
	void create(const T& data, Usage usage)
	{
		Buffer::create(std::span(&data, 1), usage);
		create();
	}
	template<StandardLayout T>
	void update(const T& data)
	{
		Buffer::update(std::span(&data, 1), 0);
	}
	template<StandardLayout T, auto T::* Member>
	void update(const member_ptr_to_type_t<decltype(Member)>& data)
	{
		Buffer::update(Span(&data, 1), getMemberOffset<T, Member>());
	}
	template<StandardLayout T, Access A>
	RestrictedSpan<T, A> map()
	{
		return Buffer::map<T, A>();
	}
	//Returns the OpenGL binding point
	[[nodiscard]] uint32_t bindingPoint() const;
	
private:
	void create();
	template<typename T, auto T::* Member>
	constexpr static size_t getMemberOffset()
	{
		return reinterpret_cast<size_t>(&(reinterpret_cast<T*>(0)->*Member));
	}

	static uint32_t CurrentBindingPoint;

	uint32_t mBindingPoint = -1;
};
