#pragma once
#include "Texture.hpp"
#include "Color.hpp"
#include <span>
#include <assert.h>

class Image : public Uncopyable
{
public:
	enum FileFormat
	{
		PNG,
		BMP,
		TGA,
		JPG
	};

	Image() = default;
	Image(Image&& image) noexcept;
	Image& operator=(Image&& image) noexcept;
	//Creates image from file
	explicit Image(const std::string& filePath);
	//Creates image from texture (GPU memory)
	explicit Image(const Texture& texture);
	//Creates image with uninitialized memory
	explicit Image(const Vec2i& size, Texture::Format format);
	~Image();
	//Creates image from file
	void create(const std::string& filePath);
	//Creates image from texture (GPU memory)
	void create(const Texture& texture);
	//Creates image with uninitialized memory
	void create(const Vec2i& size, Texture::Format format);
	//Update pixels from texture (sizes must match)
	void update(const Texture& texture);
	//Save image to file
	void save(const std::string& filePath, FileFormat format) const;
	//Returns the image 2D size
	[[nodiscard]] const Vec2i& size() const;

	/*!
	 * @brief Get pixel from pos
	 * @tparam T Pixel type
	 * @param pos Pixel pos
	 */
	template<typename T>
	T& pixel(const Vec2i& pos);
	template<>
	uint8_t& pixel(const Vec2i& pos)
	{
		assert(mFormat == Texture::Format::R);
		assert(pos.x < mSize.x && pos.y < mSize.y);
		return mPixels[pos.y * mSize.x + pos.x];
	}
	template<>
	Color32RG& pixel(const Vec2i& pos)
	{
		assert(mFormat == Texture::Format::RG);
		assert(pos.x < mSize.x && pos.y < mSize.y);
		return reinterpret_cast<Color32RG*>(mPixels)[pos.y * mSize.x + pos.x];
	}
	template<>
	Color32RGB& pixel(const Vec2i& pos)
	{
		assert(mFormat == Texture::Format::RGB);
		assert(pos.x < mSize.x && pos.y < mSize.y);
		return reinterpret_cast<Color32RGB*>(mPixels)[pos.y * mSize.x + pos.x];
	}
	template<>
	Color32& pixel(const Vec2i& pos)
	{
		assert(mFormat == Texture::Format::RGBA);
		assert(pos.x < mSize.x && pos.y < mSize.y);
		return reinterpret_cast<Color32*>(mPixels)[pos.y * mSize.x + pos.x];
	}

	/*!
	 * @brief Get pixel from pos
	 * @tparam T Pixel type
	 * @param pos Pixel pos
	 */
	template<typename T>
	const T& pixel(const Vec2i& pos) const;

	template<>
	const uint8_t& pixel(const Vec2i& pos) const
	{
		assert(mFormat == Texture::Format::R);
		assert(pos.x < mSize.x && pos.y < mSize.y);
		return mPixels[pos.y * mSize.x + pos.x];
	}
	template<>
	const Color32RG& pixel(const Vec2i& pos) const
	{
		assert(mFormat == Texture::Format::RG);
		assert(pos.x < mSize.x && pos.y < mSize.y);
		return reinterpret_cast<Color32RG*>(mPixels)[pos.y * mSize.x + pos.x];
	}
	template<>
	const Color32RGB& pixel(const Vec2i& pos) const
	{
		assert(mFormat == Texture::Format::RGB);
		assert(pos.x < mSize.x && pos.y < mSize.y);
		return reinterpret_cast<Color32RGB*>(mPixels)[pos.y * mSize.x + pos.x];
	}
	template<>
	const Color32& pixel(const Vec2i& pos) const
	{
		assert(mFormat == Texture::Format::RGBA);
		assert(pos.x < mSize.x && pos.y < mSize.y);
		return reinterpret_cast<Color32*>(mPixels)[pos.y * mSize.x + pos.x];
	}

	/*!
	 * @brief Get image pixels
	 * @tparam T Pixel type
	 */
	template<typename T>
	std::span<T> pixels();

	template<>
	std::span<uint8_t> pixels()
	{
		assert(mFormat == Texture::Format::R);
		return std::span(mPixels, static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
	}
	template<>
	std::span<Color32RG> pixels()
	{
		assert(mFormat == Texture::Format::RG);
		return std::span(reinterpret_cast<Color32RG*>(mPixels), static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
	}
	template<>
	std::span<Color32RGB> pixels()
	{
		assert(mFormat == Texture::Format::RGB);
		return std::span(reinterpret_cast<Color32RGB*>(mPixels), static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
	}
	template<>
	std::span<Color32> pixels()
	{
		assert(mFormat == Texture::Format::RGBA);
		return std::span(reinterpret_cast<Color32*>(mPixels), static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
	}

	/*!
	 * @brief Get image pixels
	 * @tparam T Pixel type
	 */
	template<typename T>
	std::span<const T> pixels() const;

	template<>
	std::span<const uint8_t> pixels() const
	{
		assert(mFormat == Texture::Format::R);
		return std::span(mPixels, static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
	}
	template<>
	std::span<const Color32RG> pixels() const
	{
		assert(mFormat == Texture::Format::RG);
		return std::span(reinterpret_cast<const Color32RG*>(mPixels), static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
	}
	template<>
	std::span<const Color32RGB> pixels() const
	{
		assert(mFormat == Texture::Format::RGB);
		return std::span(reinterpret_cast<const Color32RGB*>(mPixels), static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
	}
	template<>
	std::span<const Color32> pixels() const
	{
		assert(mFormat == Texture::Format::RGBA);
		return std::span(reinterpret_cast<const Color32*>(mPixels), static_cast<size_t>(mSize.x) * static_cast<size_t>(mSize.y));
	}

	//Returns the raw data in bytes
	std::span<uint8_t> data();
	//Returns the raw data in bytes
	std::span<const uint8_t> data() const;
	//Returns the image format
	[[nodiscard]] Texture::Format format() const;

private:
	Vec2i mSize = Vec2i::Zero;
	uint8_t* mPixels = nullptr;
	Texture::Format mFormat = Texture::Format::RGBA;
};
