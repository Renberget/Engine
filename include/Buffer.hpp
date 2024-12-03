#pragma once
#include "RestrictedSpan.hpp"
#include "Utils/Uncopyable.hpp"
#include <span>
#include <cstdint>
#include <type_traits>
#include <typeindex>

enum class Usage : uint32_t
{
	Stream = 0x88E0, //Modified once and used a few times
	Static = 0x88E4, //Modified once and used many times
	Dynamic = 0x88E8 //Modified repeatedly and used many times
};

enum class BufferType : uint32_t
{
	Unknown,
	Array = 0x8892,
	IndicesArray = 0x8893,
	Uniform = 0x8A11
};

template<typename T>
concept StandardLayout = std::is_standard_layout_v<T>;

//A memory buffer allocated on the GPU
class Buffer : public Uncopyable
{
public:
	Buffer() = delete;
	Buffer(Buffer&& buffer) noexcept;
	Buffer& operator=(Buffer&& buffer) noexcept;
	~Buffer();
	/*!
	 * @brief Creates the buffer
	 * @param data Used data to initialize the buffer
	 * @param usage Defines how the buffer will be used
	 */
	template<StandardLayout T>
	void create(std::span<const T> data, Usage usage)
	{
		mStoredType = typeid(T);
		mSize = data.size();
		create(reinterpret_cast<const void*>(data.data()), data.size() * sizeof(T), usage);
	}
	//Copy the content of data into the buffer
	template<StandardLayout T>
	void update(std::span<const T> data, size_t offset = 0)
	{
		assert(mStoredType == typeid(T));
		assert(offset + data.size() <= mSize);
		update(reinterpret_cast<const void*>(data.data()), data.size() * sizeof(T), offset);
	}
	/*!
	 * @brief Map GPU memory to a span so it can be read/written, unmap() must be called to return the control to OpenGL
	 * @tparam T Type of contained data
	 * @tparam A Type of access to the buffer's memory, using the most adapted ones ensure optimal performance
	 * @return The span to the mapped memory
	 */
	template<StandardLayout T, Access A>
	RestrictedSpan<T, A> map()
	{
		assert(mStoredType == typeid(T));
		return RestrictedSpan<T, A>(static_cast<T*>(map(A)), mSize);
	}
	//Returns the size
	[[nodiscard]] size_t size() const;
	//Binds as target for OpenGL buffer operations
	void bind() const;
	//Unmaps the buffer
	void unmap() const;
	//Returns the stored type
	[[nodiscard]] const std::type_index& storedType() const;
	//Returns OpenGL handle
	[[nodiscard]] uint32_t id() const;

protected:
	explicit Buffer(BufferType type, std::type_index storedType = typeid(void));

private:
	void create(const void* data, size_t size, Usage usage);
	void update(const void* data, size_t size, size_t offset);
	[[nodiscard]] void* map(Access access) const;

	size_t mSize = 0;
	uint32_t mId = 0;
	BufferType mType = BufferType::Unknown;
	std::type_index mStoredType;
};
