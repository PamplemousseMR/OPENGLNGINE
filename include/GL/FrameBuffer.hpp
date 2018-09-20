#pragma once

#include <assert.h>
#include <vector>

#include "GL/IGLObject.hpp"
#include "GL/RenderBuffer.hpp"
#include "GL/Texture.hpp"

namespace GL
{

class FrameBuffer : public IGLObject
{

public:

    FrameBuffer();
    ~FrameBuffer() noexcept;
    FrameBuffer(const FrameBuffer&);
    FrameBuffer(FrameBuffer&&) = delete;
    FrameBuffer& operator=(const FrameBuffer&);
    FrameBuffer& operator=(FrameBuffer&&) = delete;

    void attachColorTexture(const GL::Texture&, unsigned);
    void attachDepthTexture(const GL::Texture&) const noexcept;
    inline void attachDepthBuffer(const GL::RenderBuffer&) const noexcept;
    void checkStatus() const;
    void attachDrawBuffers() const;

    inline virtual void bind() const noexcept;
    inline virtual void unbind() const noexcept;

private:

    static GLint s_maxAttachement;
    static GLint s_maxDraw;
    static bool s_first;

private:

    std::vector< unsigned > m_colorAttachement {};

};

inline void FrameBuffer::attachDepthTexture(const GL::Texture& _texture) const noexcept
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _texture.getId(), 0);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::attachDepthBuffer(const GL::RenderBuffer& _buffer) const noexcept
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _buffer.getId());
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

}

