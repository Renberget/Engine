#include "Image.hpp"
#include "Glfw.hpp"

Texture::Texture(Texture&& texture) noexcept :
	mSize(texture.mSize),
	mId(texture.mId),
	mType(texture.mType),
	mFormat(texture.mFormat)
{
	texture.mId = 0;
}

Texture& Texture::operator=(Texture&& texture) noexcept
{
	mSize = texture.mSize;
	mId = texture.mId;
	mType = texture.mType;
	mFormat = texture.mFormat;
	texture.mId = 0;
	return *this;
}

Texture::Texture(std::string_view filePath)
{
	create(filePath);
}

Texture::Texture(const Image& image)
{
	create(image);
}

Texture::Texture(const Vec2i& size, Format format, bool enableMSAA)
{
	create(size, format, enableMSAA);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mId);
}

void Texture::create(std::string_view filePath)
{
	Image image(filePath);
	mSize = image.size();
	mFormat = image.format();
	create(reinterpret_cast<const void*>(image.data().data()));
}

void Texture::create(const Image& image)
{
	mSize = image.size();
	mFormat = Format::RGBA;
	create(reinterpret_cast<const void*>(image.data().data()));
}

void Texture::create(const Vec2i& size, Format format, bool enableMSAA)
{
	mSize = size;
	mFormat = format;
	create(nullptr, enableMSAA);
}

void Texture::update(const Image& image, const Vec2i& offset, int mipmapLevel)
{
	assert(mType == GL_TEXTURE_2D);
	assert(mSize == image.size() && mFormat == image.format());
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexSubImage2D(GL_TEXTURE_2D, mipmapLevel, offset.x, offset.y, image.size().x, image.size().y, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<const void*>(image.pixels<uint8_t>().data()));
}

const Vec2i& Texture::size() const
{
	return mSize;
}

void Texture::setWrapping(Wrapping wrapping)
{
	glBindTexture(mType, mId);
	glTexParameteri(mType, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapping));
	glTexParameteri(mType, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapping));
}

void Texture::setFilters(Filter minFilter, Filter magFilter)
{
	glBindTexture(mType, mId);
	glTexParameteri(mType, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(minFilter));
	glTexParameteri(mType, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(magFilter));
}

void Texture::generateMipmap()
{
	glBindTexture(mType, mId);
	glGenerateMipmap(mType);
}

Texture::Format Texture::format() const
{
	return mFormat;
}

void Texture::bind() const
{
	glBindTexture(mType, mId);
}

uint32_t Texture::id() const
{
	return mId;
}

int32_t Texture::getInternalFormat() const
{
	switch (mFormat)
	{
	case Format::R:
		return GL_R8;
	case Format::RG:
		return GL_RG8;
	case Format::RGB:
	case Format::BGR:
		return GL_RGB8;
	case Format::RGBA:
	case Format::BGRA:
		return GL_RGBA8;
	}
	throw std::runtime_error("Invalid format");
}

void Texture::create(const void* pixels, bool enableMSAA)
{
	mType = enableMSAA ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	if (!mId)
		glGenTextures(1, &mId);
	glBindTexture(mType, mId);
	glTexParameteri(mType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(mType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (enableMSAA)
	{
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, getInternalFormat(), mSize.x, mSize.y, GL_TRUE);
		return;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, getInternalFormat(), mSize.x, mSize.y, 0, static_cast<GLenum>(mFormat), GL_UNSIGNED_BYTE, pixels);
}
