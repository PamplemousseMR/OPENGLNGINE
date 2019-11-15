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
        FM_COLOR = GL_COLOR_BUFFER_BIT,
        FM_DEPTH = GL_DEPTH_BUFFER_BIT,
        FM_STENCIL = GL_STENCIL_BUFFER_BIT
    };

public:

    static void bindDefault();
    static void unbindDefault();
    static void bindDrawDefault();
    static void unbindDrawDefault();
    static void bindReadDefault();
    static void unbindReadDefault();
    static void blit(int, int, FRAMBUFFER_MASK);

public:

    FrameBuffer();
    ~FrameBuffer() final;
    FrameBuffer(const FrameBuffer&);
    FrameBuffer(FrameBuffer&&) = delete;
    FrameBuffer& operator=(const FrameBuffer&);
    FrameBuffer& operator=(FrameBuffer&&) = delete;

    void attachColorTexture(const GL::Texture&, unsigned);
    void attachDepthTexture(const GL::Texture&) const;
    void attachDepthStencilTexture(const GL::Texture&) const;

    void attachColorBuffer(const GL::RenderBuffer&, unsigned);
    inline void attachDepthBuffer(const GL::RenderBuffer&) const;
    inline void attachDepthStencilBuffer(const GL::RenderBuffer&) const;

    void checkStatus() const;
    void attachDrawBuffers() const;

    inline virtual void bind() const final;
    inline virtual void unbind() const final;
    inline virtual void bindDraw() const;
    inline virtual void unbindDraw() const;
    inline virtual void bindRead() const;
    inline virtual void unbindRead() const;

private:

    static GLint s_maxAttachement;
    static GLint s_maxDraw;
    static bool s_first;

private:

    std::vector< unsigned > m_colorAttachement {};

};

inline void FrameBuffer::attachDepthBuffer(const GL::RenderBuffer& _buffer) const
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _buffer.getId());
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::attachDepthStencilBuffer(const GL::RenderBuffer& _buffer) const
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _buffer.getId());
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::bindDraw() const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::unbindDraw() const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::bindRead() const
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::unbindRead() const
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

}

