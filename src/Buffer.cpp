#include "Buffer.hpp"
#include "Glfw.hpp"

Buffer::Buffer(Buffer&& buffer) noexcept :
	mSize(buffer.mSize),
	mId(buffer.mId),
	mType(buffer.mType),
	mStoredType(buffer.mStoredType)
{
	buffer.mId = 0;
}

Buffer& Buffer::operator=(Buffer&& buffer) noexcept
{
	mSize = buffer.mSize;
	mId = buffer.mId;
	mType = buffer.mType;
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

void Buffer::bind() const
{
	glBindBuffer(static_cast<GLenum>(mType), mId);
}

void Buffer::unmap() const
{
	glBindBuffer(static_cast<GLenum>(mType), mId);
	glUnmapBuffer(static_cast<GLenum>(mType));
}

const std::type_index& Buffer::storedType() const
{
	return mStoredType;
}

uint32_t Buffer::id() const
{
	return mId;
}

Buffer::Buffer(BufferType type, std::type_index storedType) : mType(type), mStoredType(storedType) {}

void Buffer::create(const void* data, size_t size, Usage usage)
{
	if (!mId)
		glGenBuffers(1, &mId);
	glBindBuffer(static_cast<GLenum>(mType), mId);
	glBufferData(static_cast<GLenum>(mType), static_cast<GLsizeiptr>(size), data, static_cast<GLenum>(usage));
}

void Buffer::update(const void* data, size_t size, size_t offset)
{
	glBindBuffer(static_cast<GLenum>(mType), mId);
	glBufferSubData(static_cast<GLenum>(mType), static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
}

void* Buffer::map(Access access) const
{
	glBindBuffer(static_cast<GLenum>(mType), mId);
	return glMapBuffer(static_cast<GLenum>(mType), static_cast<GLenum>(access));
}
