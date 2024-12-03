#include "CursorImpl.hpp"

Cursor::Cursor(Standard standard)
{
	mImpl = std::make_unique<Impl>(standard);
}

Cursor::Cursor(const Image& image, const Vec2i& hotspot)
{
	mImpl = std::make_unique<Impl>(image, hotspot);
}

void Cursor::create(Standard standard)
{
	mImpl = std::make_unique<Impl>(standard);
}

void Cursor::create(const Image& image, const Vec2i& hotspot)
{
	mImpl = std::make_unique<Impl>(image, hotspot);
}
