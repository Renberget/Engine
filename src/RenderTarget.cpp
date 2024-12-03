#include "RenderTarget.hpp"
#include "Glfw.hpp"

void RenderTarget::setViewport(const IntRect& rect)
{
	bind();
	glViewport(rect.x, rect.y, rect.w, rect.h);
}

void RenderTarget::clear(const Color& color)
{
	bind();
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderTarget::clearDepth(float depth)
{
	bind();
	glClearDepth(depth);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void RenderTarget::clearStencil(int stencil)
{
	bind();
	glClearStencil(stencil);
	glClear(GL_STENCIL_BUFFER_BIT);
}

void RenderTarget::draw(const Mesh& mesh, const Shader& shader, const Blending& blending)
{
	bind();
	blending.bind();
	shader.bind();
	mesh.draw();
}
