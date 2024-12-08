#pragma once
#include "Maths/Vec2.hpp"
#include "Type.hpp"
#include "Utils/Uncopyable.hpp"
#include <string_view>

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
		Depth32F = 0x81A7,
		Depth24Stencil8 = 0x88F0,
		Depth32FStencil8 = 0x8CAD
	};

	Texture() = default;
	Texture(Texture&& texture) noexcept;
	Texture& operator=(Texture&& texture) noexcept;
	//Creates texture from file
	explicit Texture(std::string_view filePath);
	//Creates texture from image (CPU memory)
	explicit Texture(const Image& image);
	//Creates texture with uninitialized data
	explicit Texture(const Vec2i& size, Format format, bool enableMSAA = false);
	~Texture();
	//Creates texture from file
	void create(std::string_view filePath);
	//Creates texture from image (CPU memory)
	void create(const Image& image);
	//Creates texture with uninitialized data
	void create(const Vec2i& size, Format format, bool enableMSAA = false);
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
	//Set texture as target for operations
	void bind() const;
	//Returns the OpenGL handle
	[[nodiscard]] uint32_t id() const;

private:
	[[nodiscard]] int32_t getInternalFormat() const;
	void create(const void* pixels, bool enableMSAA = false);

	Vec2i mSize = Vec2i::Zero;
	uint32_t mId = 0;
	uint32_t mType = -1;
	Format mFormat = Format::RGBA;
};

