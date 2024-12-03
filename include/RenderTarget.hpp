#pragma once
#include "Rect.hpp"
#include "Color.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Blending.hpp"

class RenderTarget
{
public:
	virtual ~RenderTarget() = default;
	//Set render target viewport
	void setViewport(const IntRect& rect);
	//Clears content with color
	void clear(const Color& color = Color::Black);
	//Clears depth buffer with depth value
	void clearDepth(float depth = 1.f);
	//Clears stencil buffer with stencil value
	void clearStencil(int stencil = 0);
	//Draws a mesh to the render target
	void draw(const Mesh& mesh, const Shader& shader, const Blending& blending = Blending::Alpha);
	//Binds as current render target
	virtual void bind() = 0;
};