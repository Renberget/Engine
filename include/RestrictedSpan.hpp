#pragma once
#include <initializer_list>
#include <cstdint>
#include <assert.h>

enum class Access : uint32_t
{
	ReadOnly = 0x88B8,
	WriteOnly = 0x88B9,
	ReadWrite = 0x88BA
};

template<typename T, Access A>
class RestrictedSpan
{
public:
	RestrictedSpan() = delete;
	RestrictedSpan(const RestrictedSpan&) = default;
	RestrictedSpan& operator=(const RestrictedSpan&) = default;
	explicit RestrictedSpan(T* data, size_t size) : mData(data), mSize(size) {}
	RestrictedSpan(std::initializer_list<T> list) : mData(list.begin()), mSize(list.size()) {}
	template<typename Container>
	RestrictedSpan(Container& container) : mData(container.data()), mSize(container.size()) {}
	void set(size_t index, const T& data)
	{
		static_assert(A != Access::ReadOnly);
		assert(index < mSize);
		mData[index] = data;
	}
	[[nodiscard]] T& operator[](size_t index)
	{
		static_assert(A == Access::ReadWrite);
		assert(index < mSize);
		return mData[index];
	}
	[[nodiscard]] const T& operator[](size_t index) const
	{
		static_assert(A != Access::WriteOnly);
		assert(index < mSize);
		return mData[index];
	}
	[[nodiscard]] size_t size() const
	{
		return mSize;
	}
	[[nodiscard]] T* begin()
	{
		static_assert(A == Access::ReadWrite);
		return mData;
	}
	[[nodiscard]] T* end()
	{
		static_assert(A == Access::ReadWrite);
		return mData + mSize;
	}
	[[nodiscard]] const T* begin() const
	{
		static_assert(A != Access::WriteOnly);
		return mData;
	}
	[[nodiscard]] const T* end() const
	{
		static_assert(A != Access::WriteOnly);
		return mData + mSize;
	}
	[[nodiscard]] const T* data() const
	{
		return mData;
	}
	[[nodiscard]] T* data()
	{
		return mData;
	}

private:
	T* mData;
	size_t mSize;
};
