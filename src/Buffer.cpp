#include "Buffer.hpp"
#include "Glfw.hpp"

Buffer::Buffer(Buffer&& buffer) noexcept :
	mSize(buffer.mSize),
	mId(buffer.mId),
	mStoredType(buffer.mStoredType)
{
	buffer.mId = 0;
}

Buffer& Buffer::operator=(Buffer&& buffer) noexcept
{
	mSize = buffer.mSize;
	mId = buffer.mId;
	mStoredType = buffer.mStoredType;
	buffer.mId = 0;
	return *this;
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &mId);
}

size_t Buffer::size() const
{
	return mSize;
}

void Buffer::unmap() const
{
	glUnmapNamedBuffer(mId);
}

void Buffer::create(const void* data, size_t size, Flags<BufferFlags> flags)
{
	if (mId)
	{
		glNamedBufferData(mId, static_cast<GLsizeiptr>(size), data, flags.get(BufferFlags::DynamicStorage) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		return;
	}

	glCreateBuffers(1, &mId);
	if (flags.get(BufferFlags::Resizable))
	{
		glNamedBufferData(mId, static_cast<GLsizeiptr>(size), data, flags.get(BufferFlags::DynamicStorage) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}
	else
	{
		glNamedBufferStorage(mId, static_cast<GLsizeiptr>(size), data, flags);
	}
}

void Buffer::update(const void* data, size_t size, size_t offset)
{
	glNamedBufferSubData(mId, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
}

void* Buffer::map(Access access) const
{
	return glMapNamedBuffer(mId, static_cast<GLenum>(access));
}
