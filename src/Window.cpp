#include "WindowImpl.hpp"
#include "Glfw.hpp"

Window::Window(const CreateInfo& info)
{
	mImpl = std::make_unique<Impl>(info);
}

Window::~Window() = default;

void Window::create(const CreateInfo& info)
{
	mImpl = std::make_unique<Impl>(info);
}

void Window::setTitle(const std::string& title)
{
	mImpl->setTitle(title);
}

void Window::setIcon(const Image& icon)
{
	mImpl->setIcon(icon);
}

void Window::setCursor(const std::shared_ptr<Cursor>& cursor)
{
	mImpl->setCursor(cursor);
}

void Window::setCursorMode(Cursor::Mode cursorMode)
{
	mImpl->setCursorMode(cursorMode);
}

void Window::setSize(const Vec2i& size)
{
	mImpl->setSize(size);
}

const Vec2i& Window::getSize() const
{
	return mImpl->getSize();
}

void Window::swapBuffers()
{
	mImpl->swapBuffers();
}

void Window::bind()
{
	mImpl->bind();
}

bool Window::shouldClose() const
{
	return mImpl->shouldClose();
}

void Window::close()
{
	mImpl->close();
}

std::function<bool()>& Window::closeCallback()
{
	return mImpl->closeCallback();
}

Delegate<bool>& Window::focusCallback()
{
	return mImpl->focusCallback();
}

Delegate<const Vec2i&>& Window::resizeCallback()
{
	return mImpl->resizeCallback();
}
