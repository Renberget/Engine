#pragma once
#include "RenderTarget.hpp"
#include <optional>

class Window;

//A texture that can be drawn to
class RenderTexture : public RenderTarget, public Uncopyable
{
public:
	RenderTexture(RenderTexture&& renderTexture) noexcept;
	RenderTexture& operator=(RenderTexture&& renderTexture) noexcept;
	//Creates render texture with uninitialized memory
	RenderTexture(const Vec2i& size, Texture::Format format, std::optional<Texture::DepthStencilFormat> depthStencilFormat = std::nullopt, bool enableMSAA = false);
	~RenderTexture() override;
	//Creates render texture with uninitialized memory
	void create(const Vec2i& size, Texture::Format format, std::optional<Texture::DepthStencilFormat> depthStencilFormat = std::nullopt, bool enableMSAA = false);
	//Blit the render texture to dstWindow
	void blit(Window& dstWindow) const;
	//Blit the render texture to dstRenderTexture
	void blit(RenderTexture& dstRenderTexture) const;
	//Blit the render texture to dstWindow using rects
	void blit(Window& dstWindow, const IntRect& srcRect, const IntRect& dstRect) const;
	//Blit the render texture to dstRenderTexture using rects
	void blit(RenderTexture& dstRenderTexture, const IntRect& srcRect, const IntRect& dstRect) const;
	//Returns the underlying texture
	[[nodiscard]] const Texture& texture() const;
	//Returns the frame buffer openGL handle
	[[nodiscard]] uint32_t id() const;
	//Binds render texture for OpenGL draw operations
	void bind() override;

private:
	Texture mTexture;
	uint32_t mFramebufferId = 0;
	uint32_t mRenderbufferId = 0;
};
