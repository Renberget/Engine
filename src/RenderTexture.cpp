#include "RenderTexture.hpp"
#include "Glfw.hpp"
#include "Window.hpp"

RenderTexture::RenderTexture(RenderTexture&& renderTexture) noexcept :
	mTexture(std::move(renderTexture.mTexture)),
	mFramebufferId(renderTexture.mFramebufferId),
	mRenderbufferId(renderTexture.mRenderbufferId)
{
	renderTexture.mFramebufferId = 0;
	renderTexture.mRenderbufferId = 0;
}

RenderTexture& RenderTexture::operator=(RenderTexture&& renderTexture) noexcept
{
	mTexture = std::move(renderTexture.mTexture);
	mFramebufferId = renderTexture.mFramebufferId;
	mRenderbufferId = renderTexture.mRenderbufferId;
	renderTexture.mFramebufferId = 0;
	renderTexture.mRenderbufferId = 0;
	return *this;
}

RenderTexture::RenderTexture(const Vec2i& size, Texture::Format format, std::optional<Texture::DepthStencilFormat> depthStencilFormat, bool enableMSAA)
{
	create(size, format, depthStencilFormat, enableMSAA);
}

RenderTexture::~RenderTexture()
{
	glDeleteFramebuffers(1, &mFramebufferId);
	glDeleteRenderbuffers(1, &mRenderbufferId);
}

void RenderTexture::create(const Vec2i& size, Texture::Format format, std::optional<Texture::DepthStencilFormat> depthStencilFormat, bool enableMSAA)
{
	if (!mFramebufferId)
		glGenFramebuffers(1, &mFramebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferId);
	
	mTexture.create(size, format, enableMSAA);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, enableMSAA ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, mTexture.id(), 0);
	
	if (depthStencilFormat.has_value())
	{
		if (!mRenderbufferId)
			glGenRenderbuffers(1, &mRenderbufferId);
		glBindRenderbuffer(GL_RENDERBUFFER, mRenderbufferId);
		glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLenum>(depthStencilFormat.value()), size.x, size.y);
		GLenum attachment;
		switch (depthStencilFormat.value())
		{
		case Texture::DepthStencilFormat::Depth16:
		case Texture::DepthStencilFormat::Depth24:
		case Texture::DepthStencilFormat::Depth32F:
			attachment = GL_DEPTH_ATTACHMENT;
			break;
		case Texture::DepthStencilFormat::Depth24Stencil8:
		case Texture::DepthStencilFormat::Depth32FStencil8:
			attachment = GL_DEPTH_STENCIL_ATTACHMENT;
			break;
		default:
			throw std::runtime_error("Invalid depth stencil format");
		}
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, mRenderbufferId);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("Failed to create framebuffer");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::blit(Window& dstWindow) const
{
	const Vec2i& sourceSize = mTexture.size();
	const Vec2i& destinationSize = dstWindow.getSize();
	blit(dstWindow, { 0, 0, sourceSize.x, sourceSize.y }, { 0, 0, destinationSize.x, destinationSize.y });
}

void RenderTexture::blit(RenderTexture& dstRenderTexture) const
{
	const Vec2i& sourceSize = mTexture.size();
	const Vec2i& destinationSize = dstRenderTexture.texture().size();
	blit(dstRenderTexture, { 0, 0, sourceSize.x, sourceSize.y }, { 0, 0, destinationSize.x, destinationSize.y });
}

void RenderTexture::blit(Window& dstWindow, const IntRect& srcRect, const IntRect& dstRect) const
{
	dstWindow.bind();
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mFramebufferId);
	glBlitFramebuffer(srcRect.x, srcRect.y, srcRect.w, srcRect.h, dstRect.x, dstRect.y, dstRect.w, dstRect.h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void RenderTexture::blit(RenderTexture& dstRenderTexture, const IntRect& srcRect, const IntRect& dstRect) const
{
	dstRenderTexture.bind();
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mFramebufferId);
	glBlitFramebuffer(srcRect.x, srcRect.y, srcRect.w, srcRect.h, dstRect.x, dstRect.y, dstRect.w, dstRect.h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

const Texture& RenderTexture::texture() const
{
	return mTexture;
}

uint32_t RenderTexture::id() const
{
	return mFramebufferId;
}

void RenderTexture::bind()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFramebufferId);
}
