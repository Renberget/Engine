#include <Engine.hpp>

struct PosColor
{
	Vec2f pos;
	Color32 color;
};

int main()
{
	Window::CreateInfo windowCreateInfo{};
	windowCreateInfo.title = "Title";
	windowCreateInfo.size = { 800, 600 };
	Window window(windowCreateInfo);

	Shader shader("Color.vert", "Color.frag");

	MeshLayout layout;
	layout.vertexLayout().add<Vec2f, Color32>();
	ArrayBuffer buffer;
	buffer.create<PosColor>(std::array<PosColor, 3>
	{
		PosColor{ { 0.f, 0.5f }, { 255, 0, 0 } },
			PosColor{ { 0.5f, -0.5f }, { 0, 255, 0 } },
			PosColor{ { -0.5f, -0.5f }, { 0, 0, 255 } }
	}, Usage::Static);
	Mesh mesh(layout, std::move(buffer));

	while (!window.shouldClose())
	{
		window.clear();
		window.draw(mesh, shader);
		window.swapBuffers();
		input::Manager::pollEvents();
	}
	return 0;
}
