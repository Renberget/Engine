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
	assert(!mFramebufferId);
	glCreateFramebuffers(1, &mFramebufferId);
	
	mTexture.create(size, format, enableMSAA);
	glNamedFramebufferTexture(mFramebufferId, GL_COLOR_ATTACHMENT0, enableMSAA ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, 0);
	
	if (depthStencilFormat.has_value())
	{
		glCreateRenderbuffers(1, &mRenderbufferId);
		glNamedRenderbufferStorage(mRenderbufferId, static_cast<GLenum>(depthStencilFormat.value()), size.x, size.y);
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
		glNamedFramebufferRenderbuffer(mFramebufferId, attachment, GL_RENDERBUFFER, mRenderbufferId);
	}

	if (glCheckNamedFramebufferStatus(mFramebufferId, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw std::runtime_error("Failed to create framebuffer");
}

void RenderTexture::setViewport(const IntRect& rect)
{
	glViewport(rect.x, rect.y, rect.w, rect.h);
}

void RenderTexture::setScissor(const IntRect& rect)
{
	glScissor(rect.x, rect.y, rect.w, rect.h);
}

void RenderTexture::clear(const Color& color)
{
	glClearNamedFramebufferfv(mFramebufferId, GL_COLOR, 0, reinterpret_cast<const GLfloat*>(&color));
}

void RenderTexture::clearDepth(float depth)
{
	glClearNamedFramebufferfv(mFramebufferId, GL_DEPTH, 0, &depth);
}

void RenderTexture::clearStencil(int stencil)
{
	glClearNamedFramebufferiv(mFramebufferId, GL_STENCIL, 0, &stencil);
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
	glBlitNamedFramebuffer(mFramebufferId, 0, srcRect.x, srcRect.y, srcRect.w, srcRect.h, dstRect.x, dstRect.y, dstRect.w, dstRect.h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void RenderTexture::blit(RenderTexture& dstRenderTexture, const IntRect& srcRect, const IntRect& dstRect) const
{
	glBlitNamedFramebuffer(mFramebufferId, dstRenderTexture.id(), srcRect.x, srcRect.y, srcRect.w, srcRect.h, dstRect.x, dstRect.y, dstRect.w, dstRect.h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void RenderTexture::draw(const Mesh& mesh, const Shader& shader, const Blending& blending)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFramebufferId);
	blending.bind();
	shader.bind();
	mesh.draw();
}

const Texture& RenderTexture::texture() const
{
	return mTexture;
}
