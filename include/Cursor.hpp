#pragma once
#include "Image.hpp"
#include <memory>

class Cursor : public Uncopyable
{
public:
	enum class Mode : int
	{
		Normal = 0x00034001,
		Hidden = 0x00034002,
		Disabled = 0x00034003,
		Captured = 0x00034004
	};

	enum class Standard : int
	{
		Arrow = 0x00036001,
		Beam = 0x00036002,
		Crosshair = 0x00036003,
		PointingHand = 0x00036004,
		ResizeEW = 0x00036005,
		ResizeNS = 0x00036006,
		ResizeNWSE = 0x00036007,
		ResizeNESW = 0x00036008,
		ResizeAll = 0x00036009,
		NotAllowed = 0x0003600A
	};

	Cursor() = default;
	//Creates a standard cursor
	explicit Cursor(Standard standard);
	/*!
	 * @brief Creates a cursor from an image
	 * @param image Source image
	 * @param hotspot The real cursor position in the image
	 */
	explicit Cursor(const Image& image, const Vec2i& hotspot = {});
	Cursor(Cursor&&) = default;
	Cursor& operator=(Cursor&&) = default;
	//Creates a standard cursor
	void create(Standard standard);
	/*!
	 * @brief Creates a cursor from an image
	 * @param image Source image
	 * @param hotspot The real cursor position in the image
	 */
	void create(const Image& image, const Vec2i& hotspot = {});

private:
	class Impl;
	std::unique_ptr<Impl> mImpl;

	friend class Window;
};