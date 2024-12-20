#include "Image.hpp"
#include "Glfw.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "External/StbImage.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "External/StbImageWrite.h"

Image::Image(Image&& image) noexcept :
	mSize(image.mSize),
	mPixels(image.mPixels),
	mFormat(image.mFormat)
{
	image.mPixels = nullptr;
}

Image& Image::operator=(Image&& image) noexcept
{
	mSize = image.mSize;
	mPixels = image.mPixels;
	mFormat = image.mFormat;
	image.mPixels = nullptr;
	return *this;
}

Image::Image(const std::filesystem::path& path)
{
	create(path);
}

Image::Image(const Texture& texture)
{
	create(texture);
}

Image::Image(const Vec2i& size, Texture::Format format)
{
	create(size, format);
}

Image::~Image()
{
	stbi_image_free(mPixels);
}

void Image::create(const std::filesystem::path& path)
{
	if (!mPixels)
		stbi_image_free(mPixels);
	
	int nbChannels;
	mPixels = stbi_load(path.string().c_str(), &mSize.x, &mSize.y, &nbChannels, 0);
	assert(mPixels);
	assert(nbChannels <= 4);
	mFormat = nbChannels == 1 ? Texture::Format::R : 
	nbChannels == 2 ? Texture::Format::RG :
	nbChannels == 3 ? Texture::Format::RGB : Texture::Format::RGBA;
}

void Image::create(const Texture& texture)
{
	if (!mPixels)
		stbi_image_free(mPixels);
	
	mSize = texture.size();
	mFormat = texture.format();
	mPixels = reinterpret_cast<uint8_t*>(stbi__malloc(4 * static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y)));
	update(texture);
}

void Image::create(const Vec2i& size, Texture::Format format)
{
	mSize = size;
	mFormat = format;
	assert(mFormat == Texture::Format::R || mFormat == Texture::Format::RG || mFormat == Texture::Format::RGB || mFormat == Texture::Format::RGBA);
	const size_t nbChannels = format == Texture::Format::R ? 1 :
	format == Texture::Format::RG ? 2 :
	format == Texture::Format::RGB ? 3 : 4;
	stbi__malloc(nbChannels * static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
}

void Image::update(const Texture& texture)
{
	assert(mSize == texture.size() && mFormat == texture.format());
	glGetTextureImage(texture.id(), 0, static_cast<GLenum>(mFormat), GL_UNSIGNED_BYTE, mSize.x * mSize.y, reinterpret_cast<void*>(mPixels));
}

void Image::save(const std::filesystem::path& path, FileFormat format) const
{
	switch (format)
	{
	case FileFormat::PNG:
		stbi_write_png(path.string().c_str(), mSize.x, mSize.y, 4, reinterpret_cast<const void*>(mPixels), 4 * mSize.x);
		return;
	case FileFormat::BMP:
		stbi_write_bmp(path.string().c_str(), mSize.x, mSize.y, 4, reinterpret_cast<const void*>(mPixels));
		return;
	case FileFormat::TGA:
		stbi_write_tga(path.string().c_str(), mSize.x, mSize.y, 4, reinterpret_cast<const void*>(mPixels));
		return;
	case FileFormat::JPG:
		constexpr int jpgMaxQuality = 100;
		stbi_write_jpg(path.string().c_str(), mSize.x, mSize.y, 4, reinterpret_cast<const void*>(mPixels), jpgMaxQuality);
		return;
	}
}

const Vec2i& Image::size() const
{
	return mSize;
}

std::span<uint8_t> Image::data()
{
	const size_t formatSize =
		mFormat == Texture::Format::R ? 1 :
		mFormat == Texture::Format::RG ? 2 :
		mFormat == Texture::Format::RGB ? 3 : 4;
	return std::span(mPixels, formatSize * static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
}

std::span<const uint8_t> Image::data() const
{
	const size_t formatSize =
		mFormat == Texture::Format::R ? 1 :
		mFormat == Texture::Format::RG ? 2 :
		mFormat == Texture::Format::RGB ? 3 : 4;
	return std::span(mPixels, formatSize * static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
}

Texture::Format Image::format() const
{
	return mFormat;
}
