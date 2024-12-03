#include "WindowImpl.hpp"
#include "MonitorImpl.hpp"
#include "CursorImpl.hpp"
#include "Input/Impl.hpp"

Window::Impl* Window::Impl::sFocusedWindow = nullptr;

Window::Impl::Impl(const CreateInfo& info)
{
	Glfw::ensureInit();

	setHints(info);
	initWindow(info);
	enableGlCapabilities(info);
	setCallbacks();

	sFocusedWindow = this;
}

Window::Impl::~Impl()
{
	glfwSetWindowShouldClose(mHandle, GLFW_TRUE);
}

void Window::Impl::setTitle(const std::string& title)
{
	glfwSetWindowTitle(mHandle, title.c_str());
}

void Window::Impl::setIcon(const Image& icon)
{
	const Vec2i& size = icon.size();
	const GLFWimage glfwImage
	{
		size.x,
		size.y,
		const_cast<uint8_t*>(icon.pixels<uint8_t>().data())
	};
	glfwSetWindowIcon(mHandle, 1, &glfwImage);
}

void Window::Impl::setCursor(const std::shared_ptr<Cursor>& cursor)
{
	mCursor = cursor;
	glfwSetCursor(mHandle, cursor ? cursor->mImpl->handle() : nullptr);
}

void Window::Impl::setCursorMode(Cursor::Mode cursorMode)
{
	glfwSetInputMode(mHandle, GLFW_CURSOR, static_cast<int>(cursorMode));
}

void Window::Impl::setSize(const Vec2i& size)
{
	glfwSetWindowSize(mHandle, size.x, size.y);
}

const Vec2i& Window::Impl::getSize() const
{
	return mSize;
}

void Window::Impl::swapBuffers()
{
	glfwSwapBuffers(mHandle);
}

bool Window::Impl::shouldClose() const
{
	return glfwWindowShouldClose(mHandle);
}

void Window::Impl::close()
{
	glfwSetWindowShouldClose(mHandle, GLFW_TRUE);
}

std::function<bool()>& Window::Impl::closeCallback()
{
	return mCloseCallback;
}

Delegate<bool>& Window::Impl::focusCallback()
{
	return mFocusCallback;
}

Delegate<const Vec2i&>& Window::Impl::resizeCallback()
{
	return mResizeCallback;
}

void Window::Impl::bind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glfwMakeContextCurrent(mHandle);
}

GLFWwindow* Window::Impl::handle()
{
	return mHandle;
}

Window::Impl* Window::Impl::getFocusedWindow()
{
	return sFocusedWindow;
}

void Window::Impl::setHints(const CreateInfo& info)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	const VideoMode& videoMode = info.monitor ? info.monitor->videoMode() : Monitor::getPrimary().videoMode();
	mSize = info.size;
	if (mSize.x <= 0 || mSize.y <= 0)
	{
		mSize.x = videoMode.width;
		mSize.y = videoMode.height;
	}
	glfwWindowHint(GLFW_RED_BITS, videoMode.redBits);
	glfwWindowHint(GLFW_GREEN_BITS, videoMode.greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, videoMode.blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, videoMode.refreshRate);
	glfwWindowHint(GLFW_SAMPLES, info.flags.get(CreateFlag::MSAA) ? 4 : 0);
}

void Window::Impl::initWindow(const CreateInfo& info)
{
	GLFWwindow* oldHandle = mHandle;
	mHandle = glfwCreateWindow(mSize.x, mSize.y, info.title.c_str(), info.monitor ? info.monitor->mImpl->handle() : nullptr, info.share ? info.share->mImpl->mHandle : oldHandle);
	if (!mHandle)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create window");
	}
	glfwMakeContextCurrent(mHandle);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		glfwTerminate();
		throw std::runtime_error("Failed to init glad");
	}

	if (oldHandle)
		glfwSetWindowShouldClose(oldHandle, GLFW_TRUE);
}

void Window::Impl::enableGlCapabilities(const CreateInfo& info)
{
	if (info.flags.get(CreateFlag::Blending))
		glEnable(GL_BLEND);
	if (info.flags.get(CreateFlag::DepthTest))
		glEnable(GL_DEPTH_TEST);
	if (info.flags.get(CreateFlag::StencilTest))
		glEnable(GL_STENCIL_TEST);
	if (info.flags.get(CreateFlag::MSAA))
		glEnable(GL_MULTISAMPLE);
	if (static_cast<uint32_t>(info.cullMode))
	{
		glEnable(GL_CULL_FACE);
		glCullFace(static_cast<GLenum>(info.cullMode));
	}
}

void Window::Impl::setCallbacks()
{
	glfwSetWindowCloseCallback(mHandle, closeInternalCallback);
	glfwSetWindowFocusCallback(mHandle, focusInternalCallback);
	glfwSetFramebufferSizeCallback(mHandle, resizeInternalCallback);
	glfwSetWindowUserPointer(mHandle, reinterpret_cast<void*>(this));
	input::Impl::setCallbacks(mHandle);
}

void Window::Impl::closeInternalCallback(GLFWwindow* glfwWindow)
{
	Impl* impl = static_cast<Impl*>(glfwGetWindowUserPointer(glfwWindow));
	if (impl->mCloseCallback)
	{
		if (!impl->mCloseCallback())
		{
			glfwSetWindowShouldClose(glfwWindow, GLFW_FALSE);
			return;
		}
	}
	glfwDestroyWindow(glfwWindow);
}

void Window::Impl::focusInternalCallback(GLFWwindow* glfwWindow, int focused)
{
	Impl* impl = static_cast<Impl*>(glfwGetWindowUserPointer(glfwWindow));
	if (focused)
		sFocusedWindow = impl;
	if (impl->mFocusCallback)
		impl->mFocusCallback(static_cast<bool>(focused));
}

void Window::Impl::resizeInternalCallback(GLFWwindow* glfwWindow, int width, int height)
{
	Impl* impl = static_cast<Impl*>(glfwGetWindowUserPointer(glfwWindow));
	impl->setSize({ width, height });
	if (impl->mResizeCallback)
		impl->mResizeCallback({ width, height });
}