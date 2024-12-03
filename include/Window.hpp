#pragma once
#include "Utils/Flags.hpp"
#include "Input/Manager.hpp"
#include "CullMode.hpp"
#include "Monitor.hpp"
#include "Image.hpp"
#include "RenderTexture.hpp"

//A desktop window
class Window : public RenderTarget, public Uncopyable
{
public:
	enum class CreateFlag : uint8_t
	{
		None =			0,
		Blending =		1 << 0,
		DepthTest =		1 << 1,
		StencilTest =	1 << 2,
		MSAA =			1 << 3
	};

	struct CreateInfo
	{
		std::string title;
		Vec2i size = {};
		Monitor* monitor = nullptr;
		Window* share = nullptr;
		CullMode cullMode = CullMode::None;
		Flags<CreateFlag> flags = CreateFlag::Blending;
	};

	Window() = default;
	explicit Window(const CreateInfo& info);
	~Window() override;
	
	//Creates new window
	void create(const CreateInfo& info);
	//Set the window title
	void setTitle(const std::string& title);
	//Set the window icon
	void setIcon(const Image& icon);
	//Set the new cursor, pass nullptr to reset to default
	void setCursor(const std::shared_ptr<Cursor>& cursor);
	//Set the cursor mode
	void setCursorMode(Cursor::Mode cursorMode);
	//Set the window size
	void setSize(const Vec2i& size);
	//Returns window size
	[[nodiscard]] const Vec2i& getSize() const;

	//Swaps the front and back buffer and display everything drawn since last swap
	void swapBuffers();
	//Binds the window as current render target
	void bind() override;

	//Indicate whether the window should close or not 
	bool shouldClose() const;
	//Try to close the window
	void close();

	//Returns window close callback
	[[nodiscard]] std::function<bool()>& closeCallback();
	//Returns window focus callback
	[[nodiscard]] Delegate<bool>& focusCallback();
	//Returns window resize callback
	[[nodiscard]] Delegate<const Vec2i&>& resizeCallback();

private:
	class Impl;
	std::unique_ptr<Impl> mImpl;

	friend class input::Impl;
};
