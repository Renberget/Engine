#include <Engine.hpp>

constexpr const char* VertexCode = "\
#version 330 core\n\
\n\
layout (location = 0) in vec2 iPos;\n\
layout (location = 1) in vec2 iUv;\n\
\n\
out vec2 uv;\n\
\n\
void main()\n\
{\n\
	uv = iUv;\n\
	gl_Position = vec4(iPos, 0.0, 1.0);\n\
}\n\
";

constexpr const char* FragmentCode = "\
#version 330 core\n\
\n\
in vec2 uv;\n\
\n\
out vec4 FragColor;\n\
\n\
uniform sampler2D texture;\n\
\n\
void main()\n\
{\n\
	FragColor = texture2D(texture, uv);\n\
}\n\
";

struct PosUv
{
	Vec2f pos;
	Vec2f uv;
};

int main()
{
	Window::CreateInfo windowCreateInfo{};
	windowCreateInfo.title = "Title";
	windowCreateInfo.size = { 800, 600 };
	Window window(windowCreateInfo);

	Texture texture("sprite.png");
	texture.setFilters(Texture::Nearest, Texture::Nearest);

	Shader shader;
	shader.createFromData(VertexCode, FragmentCode);
	shader.setUniform("texture", texture);

	MeshLayout layout;
	layout.add<Vec2f, Vec2f>();

	FloatRect spriteRect(-0.25f, -0.25f, 0.5f, 0.5f);

	Mesh mesh;
	mesh.vertices().create<PosUv>(std::array<PosUv, 4>
	{
		PosUv{ { spriteRect.x, spriteRect.endY() }, { 0.f, 0.f } },
			PosUv{ { spriteRect.endX(), spriteRect.endY() }, { 1.f, 0.f } },
			PosUv{ { spriteRect.endX(), spriteRect.y }, { 1.f, 1.f } },
			PosUv{ { spriteRect.x, spriteRect.y }, { 0.f, 1.f } }
	}, Usage::Static);
	mesh.indices().create<uint16_t>(std::array<uint16_t, 6>
	{
		0, 1, 2, 2, 3, 0
	}, Usage::Static);
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