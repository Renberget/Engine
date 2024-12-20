#pragma once
#include "RestrictedSpan.hpp"
#include "Utils/Flags.hpp"
#include "Utils/Uncopyable.hpp"
#include <span>
#include <typeindex>

//A memory buffer handled by OpenGL
class Buffer : public Uncopyable
{
public:
	enum BufferFlags : uint32_t
	{
		DynamicStorage = 0x0100, //The buffer can be updated
		MapRead = 0x0001, //The buffer can be mapped with read access
		MapWrite = 0x0002, //The buffer can be mapped with write access
		MapPersistent = 0x0040, //The buffer can be used while mapped, must be used with at least one of MapRead and MapWrite
		MapCoherent = 0x0080, //Makes the mapping coherent with OpenGL, must be set with MapPersistent
		ClientStorage = 0x0200, //The buffer may be stored on CPU memory
		Resizable = 0x1000 //The buffer can be updated with data of different size
	};

	Buffer(Buffer&& buffer) noexcept;
	Buffer& operator=(Buffer&& buffer) noexcept;
	~Buffer();
	//Creates a buffer with uninitialized data or resize it if the flag is enabled
	template<typename T>
	void create(size_t size, Flags<BufferFlags> flags = {})
	{
		mStoredType = typeid(T);
		mSize = size;
		create(nullptr, size * sizeof(T), flags);
	}
	/*!
	 * @brief Creates the buffer or resize it if the flag is enabled
	 * @param data Used data to initialize the buffer
	 * @param flags Defines the buffer capabilities
	 */
	template<typename T>
	void create(std::initializer_list<T> data, Flags<BufferFlags> flags = {})
	{
		mStoredType = typeid(T);
		mSize = data.size();
		create(reinterpret_cast<const void*>(data.begin()), data.size() * sizeof(T), flags);
	}
	/*!
	 * @brief Creates the buffer or resize it if the flag is enabled
	 * @param data Used data to initialize the buffer
	 * @param flags Defines the buffer capabilities
	 */
	template<typename T>
	void create(std::span<const T> data, Flags<BufferFlags> flags = {})
	{
		mStoredType = typeid(T);
		mSize = data.size();
		create(reinterpret_cast<const void*>(data.data()), data.size() * sizeof(T), flags);
	}
	//Copy the content of data into the buffer
	template<typename T>
	void update(std::initializer_list<T> data, size_t offset = 0)
	{
		assert(mStoredType == typeid(T));
		update(reinterpret_cast<const void*>(data.begin()), data.size() * sizeof(T), offset);
	}
	//Copy the content of data into the buffer
	template<typename T>
	void update(std::span<const T> data, size_t offset = 0)
	{
		assert(mStoredType == typeid(T));
		update(reinterpret_cast<const void*>(data.data()), data.size() * sizeof(T), offset);
	}
	/*!
	 * @brief Map GPU memory to a span so it can be read/written, unmap() must be called to return the control to OpenGL, be sure to enable the necessary flags
	 * @tparam T Type of contained data
	 * @tparam A Type of access to the buffer's memory, using the most adapted ones ensure optimal performance
	 * @return The span to the mapped memory
	 */
	template<typename T, Access A>
	RestrictedSpan<T, A> map()
	{
		assert(mStoredType == typeid(T));
		return RestrictedSpan<T, A>(static_cast<T*>(map(A)), mSize);
	}
	//Returns the size
	[[nodiscard]] size_t size() const;
	//Unmaps the buffer
	void unmap() const;
	//Returns the stored type
	[[nodiscard]] inline const std::type_index& storedType() const { return mStoredType; }
	//Returns OpenGL handle
	[[nodiscard]] inline uint32_t id() const { return mId; }

protected:
	Buffer() = default;

private:
	void create(const void* data, size_t size, Flags<BufferFlags> flags);
	void update(const void* data, size_t size, size_t offset);
	[[nodiscard]] void* map(Access access) const;

	size_t mSize = 0;
	std::type_index mStoredType = typeid(void);
	uint32_t mId = 0;
};
