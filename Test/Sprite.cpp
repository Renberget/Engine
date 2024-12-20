#include <Engine.hpp>

constexpr const char* VertexCode = "\
#version 460 core\n\
\n\
layout (location = 0) in vec2 iPos;\n\
layout (location = 1) in vec2 iUv;\n\
\n\
out vec2 uv;\n\
\n\
uniform mat4 projection;\n\
uniform mat4 view;\n\
uniform mat3 model;\n\
\n\
void main()\n\
{\n\
	uv = iUv;\n\
	gl_Position = projection * view * vec4(model * vec3(iPos, 1.0), 1.0);\n\
}\n\
";

constexpr const char* FragmentCode = "\
#version 460 core\n\
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

	GlslShader shader;
	shader.createFromCode(VertexCode, FragmentCode);
	shader.setUniform("texture", texture);

	MeshLayout layout;
	layout.create<PosUv, &PosUv::pos, &PosUv::uv>();

	Vec2f windowSize = Vec2f(window.getSize());

	Mat4f projection = math::ortho(0.f, windowSize.x, 0.f, windowSize.y, 0.1f, 10.f);
	Transform3f view(Vec3f(0.5f * windowSize.x, 0.5f * windowSize.y, -5.f));
	Transform2f model = Transform2f::identity();

	shader.setUniform("projection", projection);
	shader.setUniform("view", view);

	FloatRect spriteRect(-50.f, -50.f, 100.f, 100.f);

	Mesh mesh;
	mesh.vertices().create<PosUv>(
		{
			{ .pos = { spriteRect.x, spriteRect.endY() }, .uv = { 0.f, 0.f } },
			{ .pos = { spriteRect.endX(), spriteRect.endY() }, .uv = { 1.f, 0.f } },
			{ .pos = { spriteRect.endX(), spriteRect.y }, .uv = { 1.f, 1.f } },
			{ .pos = { spriteRect.x, spriteRect.y }, .uv = { 0.f, 1.f } }
		});
	mesh.indices().create<uint16_t>(
		{
			0, 1, 2, 2, 3, 0
		});
	mesh.create(layout);

	Clock clock;
	while (!window.shouldClose())
	{
		float seconds = clock.getSeconds();

		model.setRotation(2.f * seconds);
		model.setPosition(100.f * Vec2f(cos(seconds), sin(seconds)));
		model.setScale(1.f + 0.5f * sin(seconds));
		shader.setUniform("model", model);

		window.clear();
		window.draw(mesh, shader);
		window.swapBuffers();

		input::Manager::pollEvents();
	}

	return 0;
}
