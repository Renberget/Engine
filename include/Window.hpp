#pragma once
#include "Utils/Flags.hpp"
#include "Input/Manager.hpp"
#include "CullMode.hpp"
#include "Monitor.hpp"
#include "Image.hpp"
#include "RenderTexture.hpp"

//A desktop window
class Window : public RenderTexture
{
public:
	enum CreateFlag : uint8_t
	{
		None =			0,
		PrintDebug =	1 << 0,
		Blend =			1 << 1,
		Scissor =		1 << 2,
		DepthTest =		1 << 3,
		StencilTest =	1 << 4,
		MSAA =			1 << 5
	};

	struct CreateInfo
	{
		std::string title;
		Vec2i size = {};
		Monitor* monitor = nullptr;
		Window* share = nullptr;
		CullMode cullMode = CullMode::None;
		Flags<CreateFlag> flags = CreateFlag::Blend;
	};

	Window() = default;
	explicit Window(const CreateInfo& info);
	~Window();
	
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
	//Draws a mesh
	void draw(const Mesh& mesh, const Shader& shader, const Blending& blending = Blending::Alpha);

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
