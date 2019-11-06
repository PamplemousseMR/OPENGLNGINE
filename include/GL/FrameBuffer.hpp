#pragma once

#include <assert.h>
#include <vector>

#include "GL/IBindable.hpp"
#include "GL/RenderBuffer.hpp"
#include "GL/Texture.hpp"

namespace GL
{

class FrameBuffer : public IBindable
{

public:

    enum FRAMBUFFER_MASK : GLbitfield
    {
        MASK_COLOR = GL_COLOR_BUFFER_BIT,
        MASK_DEPTH = GL_DEPTH_BUFFER_BIT,
        MASK_STENCIL = GL_STENCIL_BUFFER_BIT
    };

public:

    static void bindDefault() noexcept;
    static void unbindDefault() noexcept;
    static void bindDrawDefault() noexcept;
    static void unbindDrawDefault() noexcept;
    static void bindReadDefault() noexcept;
    static void unbindReadDefault() noexcept;
    static void blit(int, int, FRAMBUFFER_MASK) noexcept;

public:

    FrameBuffer();
    ~FrameBuffer() noexcept final;
    FrameBuffer(const FrameBuffer&);
    FrameBuffer(FrameBuffer&&) = delete;
    FrameBuffer& operator=(const FrameBuffer&);
    FrameBuffer& operator=(FrameBuffer&&) = delete;

    void attachColorTexture(const GL::Texture&, unsigned);
    inline void attachDepthTexture(const GL::Texture&) const noexcept;
    inline void attachDepthStencilTexture(const GL::Texture&) const noexcept;

    void attachColorBuffer(const GL::RenderBuffer&, unsigned);
    inline void attachDepthBuffer(const GL::RenderBuffer&) const noexcept;
    inline void attachDepthStencilBuffer(const GL::RenderBuffer&) const noexcept;

    void checkStatus() const;
    void attachDrawBuffers() const;

    inline virtual void bind() const noexcept final;
    inline virtual void unbind() const noexcept final;
    inline virtual void bindDraw() const noexcept;
    inline virtual void unbindDraw() const noexcept;
    inline virtual void bindRead() const noexcept;
    inline virtual void unbindRead() const noexcept;

private:

    static GLint s_maxAttachement;
    static GLint s_maxDraw;
    static bool s_first;

private:

    std::vector< unsigned > m_colorAttachement {};

};

inline void FrameBuffer::attachDepthTexture(const GL::Texture& _texture) const noexcept
{
    switch(_texture.getType())
    {
    case Texture::TYPE_1D:
        glFramebufferTexture1D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_1D, _texture.getId(), 0);
        break;
    case Texture::TYPE_2D:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _texture.getId(), 0);
        break;
    case Texture::TYPE_2DMULTISAMPLE:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, _texture.getId(), 0);
        break;
    }
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::attachDepthStencilTexture(const GL::Texture& _texture) const noexcept
{
    switch(_texture.getType())
    {
    case Texture::TYPE_1D:
        glFramebufferTexture1D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_1D, _texture.getId(), 0);
        break;
    case Texture::TYPE_2D:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _texture.getId(), 0);
        break;
    case Texture::TYPE_2DMULTISAMPLE:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, _texture.getId(), 0);
        break;
    }
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::attachDepthBuffer(const GL::RenderBuffer& _buffer) const noexcept
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _buffer.getId());
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::attachDepthStencilBuffer(const GL::RenderBuffer& _buffer) const noexcept
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _buffer.getId());
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::bind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::unbind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::bindDraw() const noexcept
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::unbindDraw() const noexcept
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::bindRead() const noexcept
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::unbindRead() const noexcept
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

}

