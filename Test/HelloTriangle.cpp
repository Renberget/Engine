#include <Engine.hpp>

constexpr const char* VertexCode = "\
#version 460 core\n\
\n\
layout(location = 0) in vec2 iPos;\n\
layout(location = 1) in vec4 iColor;\n\
\n\
out vec4 color;\n\
\n\
void main()\n\
{\n\
	color = iColor;\n\
	gl_Position = vec4(iPos, 0.0, 1.0);\n\
}\n\
";

constexpr const char* FragmentCode = "\n\
#version 460 core\n\
\n\
out vec4 FragColor;\n\
\n\
in vec4 color;\n\
\n\
void main()\n\
{\n\
	FragColor = color;\n\
}\n\
";

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
	GlslShader shader;
	shader.createFromCode(VertexCode, FragmentCode);

	MeshLayout layout;
	layout.create<PosColor, &PosColor::pos, &PosColor::color>();

	Mesh mesh;
	mesh.vertices().create<PosColor>(
		{
			{ .pos = { 0.f, 0.5f }, .color = { 255, 0, 0 } },
			{ .pos = { 0.5f, -0.5f }, .color = { 0, 255, 0 } },
			{ .pos = { -0.5f, -0.5f }, .color = { 0, 0, 255 } }
		});
	mesh.create(layout);

	while (!window.shouldClose())
	{
		window.clear();
		window.draw(mesh, shader);
		window.swapBuffers();

		input::Manager::pollEvents();
	}
	return 0;
}
