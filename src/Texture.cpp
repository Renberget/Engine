#include "Image.hpp"
#include "Glfw.hpp"

Texture::Texture(Texture&& texture) noexcept :
	mSize(texture.mSize),
	mId(texture.mId),
	mFormat(texture.mFormat)
{
	texture.mId = 0;
}

Texture& Texture::operator=(Texture&& texture) noexcept
{
	mSize = texture.mSize;
	mId = texture.mId;
	mFormat = texture.mFormat;
	texture.mId = 0;
	return *this;
}

Texture::Texture(const std::filesystem::path& path, int mipmapCount)
{
	create(path, mipmapCount);
}

Texture::Texture(const Image& image, int mipmapCount)
{
	create(image, mipmapCount);
}

Texture::Texture(const Vec2i& size, Format format, int mipmapCount)
{
	create(size, format, mipmapCount);
}

Texture::Texture(const Vec2i& size, Format format, bool enableMSAA)
{
	create(size, format, enableMSAA);
}

Texture::~Texture()
{
	glDeleteTextures(1, &mId);
}

void Texture::create(const std::filesystem::path& path, int mipmapCount)
{
	assert(!mId);

	Image image(path);
	mSize = image.size();
	mFormat = image.format();

	glCreateTextures(GL_TEXTURE_2D, 1, &mId);
	glTextureStorage2D(mId, mipmapCount, getInternalFormat(), mSize.x, mSize.y);
	glTextureSubImage2D(mId, 0, 0, 0, mSize.x, mSize.y, static_cast<GLenum>(mFormat), GL_UNSIGNED_BYTE, reinterpret_cast<const void*>(image.data().data()));
}

void Texture::create(const Image& image, int mipmapCount)
{
	assert(!mId);

	mSize = image.size();
	mFormat = Format::RGBA;
	
	glCreateTextures(GL_TEXTURE_2D, 1, &mId);
	glTextureStorage2D(mId, mipmapCount, getInternalFormat(), mSize.x, mSize.y);
	glTextureSubImage2D(mId, 0, 0, 0, mSize.x, mSize.y, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<const void*>(image.data().data()));
}

void Texture::create(const Vec2i& size, Format format, int mipmapCount)
{
	assert(!mId);

	mSize = size;
	mFormat = format;
	
	glCreateTextures(GL_TEXTURE_2D, 1, &mId);
	glTextureStorage2D(mId, mipmapCount, getInternalFormat(), mSize.x, mSize.y);
}

void Texture::create(const Vec2i& size, Format format, bool enableMSAA)
{
	assert(!mId);

	mSize = size;
	mFormat = format;
	mEnableMSAA = enableMSAA;

	glCreateTextures(enableMSAA ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, 1, &mId);
	if (enableMSAA)
		glTextureStorage2DMultisample(mId, 4, getInternalFormat(), mSize.x, mSize.y, GL_TRUE);
}

void Texture::update(const Image& image, const Vec2i& offset, int mipmapLevel)
{
	assert(!mEnableMSAA);
	assert(mSize == image.size() && mFormat == image.format());
	glTextureSubImage2D(mId, mipmapLevel, offset.x, offset.y, image.size().x, image.size().y, mFormat, GL_UNSIGNED_BYTE, reinterpret_cast<const void*>(image.pixels<uint8_t>().data()));
}

const Vec2i& Texture::size() const
{
	return mSize;
}

void Texture::setWrapping(Wrapping wrapping)
{
	glTextureParameteri(mId, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapping));
	glTextureParameteri(mId, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapping));
}

void Texture::setFilters(Filter minFilter, Filter magFilter)
{
	glTextureParameteri(mId, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(minFilter));
	glTextureParameteri(mId, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(magFilter));
}

void Texture::generateMipmap()
{
	glGenerateTextureMipmap(mId);
}

Texture::Format Texture::format() const
{
	return mFormat;
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
