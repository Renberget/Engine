#pragma once
#include "Maths/Vec2.hpp"
#include "Utils/Uncopyable.hpp"
#include <filesystem>

class Image;

class Texture : public Uncopyable
{
public:
	enum Wrapping : int32_t
	{
		Repeat = 0x2901,
		MirroredRepeat = 0x8370,
		ClampToEdge = 0x812F,
		ClampToBorder = 0x812D
	};

	enum Filter : int32_t
	{
		Nearest = 0x2600,
		Linear = 0x2601
	};

	enum Format : uint32_t
	{
		R = 0x1903,
		RG = 0x8227,
		RGB = 0x1907,
		BGR = 0x80E0,
		RGBA = 0x1908,
		BGRA = 0x80E1
	};

	enum DepthStencilFormat : uint32_t
	{
		Depth16 = 0x81A5,
		Depth24 = 0x81A6,
		Depth32 = 0x81A7,
		Depth32F = 0x8CAC,
		Depth24Stencil8 = 0x88F0,
		Depth32FStencil8 = 0x8CAD,
		StencilIndex1 = 0x8D46,
		StencilIndex4 = 0x8D47,
		StencilIndex8 = 0x8D48,
		StencilIndex16 = 0x8D49
	};

	Texture() = default;
	Texture(Texture&& texture) noexcept;
	Texture& operator=(Texture&& texture) noexcept;
	//Creates texture from file
	explicit Texture(const std::filesystem::path& path, int mipmapCount = 1);
	//Creates texture from image (CPU memory)
	explicit Texture(const Image& image, int mipmapCount = 1);
	//Creates texture with uninitialized data
	explicit Texture(const Vec2i& size, Format format, int mipmapCount = 1);
	//Creates texture with uninitialized data
	explicit Texture(const Vec2i& size, Format format, bool enableMSAA);
	~Texture();
	//Creates texture from file
	void create(const std::filesystem::path& path, int mipmapCount = 1);
	//Creates texture from image (CPU memory)
	void create(const Image& image, int mipmapCount = 1);
	//Creates texture with uninitialized data
	void create(const Vec2i& size, Format format, int mipmapCount = 1);
	//Creates texture with uninitialized data
	void create(const Vec2i& size, Format format, bool enableMSAA);
	//Updates texture content from image data
	void update(const Image& image, const Vec2i& offset = {}, int mipmapLevel = 0);
	//Returns the texture 2D size
	[[nodiscard]] const Vec2i& size() const;
	//Set the texture wrapping
	void setWrapping(Wrapping wrapping);
	//Set the texture filters
	void setFilters(Filter minFilter, Filter magFilter);
	//Generate mipmaps for texture
	void generateMipmap();
	//Returns the texture format
	[[nodiscard]] Format format() const;
	//Returns the OpenGL handle
	[[nodiscard]] inline uint32_t id() const { return mId; }

private:
	[[nodiscard]] int32_t getInternalFormat() const;

	Vec2i mSize = Vec2i::zero();
	uint32_t mId = 0;
	Format mFormat = Format::RGBA;
	bool mEnableMSAA = false;
};

