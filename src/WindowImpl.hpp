#pragma once
#include "Window.hpp"
#include "Glfw.hpp"

class Window::Impl
{
public:
	explicit Impl(const CreateInfo& info);
	~Impl();
	void setTitle(const std::string& title);
	void setIcon(const Image& icon);

	void setCursor(const std::shared_ptr<Cursor>& cursor);
	void setCursorMode(Cursor::Mode cursorMode);

	void setSize(const Vec2i& size);
	const Vec2i& getSize() const;

	void swapBuffers();

	bool shouldClose() const;
	void close();

	[[nodiscard]] std::function<bool()>& closeCallback();
	[[nodiscard]] Delegate<bool>& focusCallback();
	[[nodiscard]] Delegate<const Vec2i&>& resizeCallback();

	void bind();
	[[nodiscard]] inline GLFWwindow* handle() { return mHandle; }
	
	static Impl* getFocusedWindow();

private:
	void setHints(const CreateInfo& info);
	void initWindow(const CreateInfo& info);
	void enableGlCapabilities(const CreateInfo& info);
	void setCallbacks();

	static void closeInternalCallback(GLFWwindow* glfwWindow);
	static void focusInternalCallback(GLFWwindow* glfwWindow, int focused);
	static void resizeInternalCallback(GLFWwindow* glfwWindow, int width, int height);

	static Impl* sFocusedWindow;

	GLFWwindow* mHandle = nullptr;
	std::shared_ptr<Cursor> mCursor;
	Vec2i mSize;
	std::function<bool()> mCloseCallback;
	Delegate<bool> mFocusCallback;
	Delegate<const Vec2i&> mResizeCallback;
};