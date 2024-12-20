#include "CursorImpl.hpp"

Cursor::Impl::Impl(const Image& image, const Vec2i& hotspot)
{
	const Vec2i& size = image.size();
	const GLFWimage glfwImage
	{
		.width = size.x,
		.height = size.y,
		.pixels = const_cast<uint8_t*>(image.pixels<uint8_t>().data())
	};
	mHandle = glfwCreateCursor(&glfwImage, hotspot.x, hotspot.y);
}

Cursor::Impl::Impl(Standard standard)
{
	mHandle = glfwCreateStandardCursor(static_cast<int>(standard));
}

Cursor::Impl::~Impl()
{
	glfwDestroyCursor(mHandle);
}

GLFWcursor* Cursor::Impl::handle()
{
	return mHandle;
}
