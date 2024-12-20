#pragma once
#include "Maths/Rect.hpp"
#include "Mesh.hpp"
#include "GlslShader.hpp"
#include "BinaryShader.hpp"
#include "Blending.hpp"
#include <optional>

class Window;

//A texture that can be drawn to
class RenderTexture : public Uncopyable
{
public:
	RenderTexture() = default;
	RenderTexture(RenderTexture&& renderTexture) noexcept;
	RenderTexture& operator=(RenderTexture&& renderTexture) noexcept;
	//Creates render texture with uninitialized memory
	RenderTexture(const Vec2i& size, Texture::Format format, std::optional<Texture::DepthStencilFormat> depthStencilFormat = std::nullopt, bool enableMSAA = false);
	~RenderTexture();
	//Creates render texture with uninitialized memory
	void create(const Vec2i& size, Texture::Format format, std::optional<Texture::DepthStencilFormat> depthStencilFormat = std::nullopt, bool enableMSAA = false);
	//Set render target viewport
	void setViewport(const IntRect& rect);
	//Set scissor
	void setScissor(const IntRect& rect);
	//Clears content with color
	void clear(const Color& color = Color::Black);
	//Clears depth buffer with depth value
	void clearDepth(float depth = 1.f);
	//Clears stencil buffer with stencil value
	void clearStencil(int stencil = 0);
	//Blit the render texture to dstWindow
	void blit(Window& dstWindow) const;
	//Blit the render texture to dstRenderTexture
	void blit(RenderTexture& dstRenderTexture) const;
	//Blit the render texture to dstWindow using rects
	void blit(Window& dstWindow, const IntRect& srcRect, const IntRect& dstRect) const;
	//Blit the render texture to dstRenderTexture using rects
	void blit(RenderTexture& dstRenderTexture, const IntRect& srcRect, const IntRect& dstRect) const;
	//Draws a mesh
	void draw(const Mesh& mesh, const Shader& shader, const Blending& blending = Blending::Alpha);
	//Returns the underlying texture
	[[nodiscard]] const Texture& texture() const;
	//Returns the frame buffer openGL handle
	[[nodiscard]] inline uint32_t id() const { return mFramebufferId; }

protected:
	Texture mTexture;
	uint32_t mFramebufferId = 0;
	uint32_t mRenderbufferId = 0;
};
