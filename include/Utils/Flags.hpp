#pragma once
#include <type_traits>

template<typename T> requires(std::is_enum_v<T>)
class Flags
{
	using UType = std::underlying_type_t<T>;
public:
	constexpr Flags() : mFlags(static_cast<UType>(0)) {}
	constexpr Flags(T flags) : mFlags(static_cast<UType>(flags)) {}

	constexpr Flags& set(T flag, bool value = true)
	{
		mFlags |= static_cast<UType>(flag);
		return *this;
	}

	constexpr bool get(T flag) const
	{
		return (mFlags & static_cast<UType>(flag)) == static_cast<UType>(flag);
	}

	operator UType() const
	{
		return mFlags;
	}

private:
	UType mFlags;
};
