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

    static inline void blit(int, int) noexcept;

public:

    FrameBuffer();
    ~FrameBuffer() noexcept override;
    FrameBuffer(const FrameBuffer&);
    FrameBuffer(FrameBuffer&&) = delete;
    FrameBuffer& operator=(const FrameBuffer&);
    FrameBuffer& operator=(FrameBuffer&&) = delete;

    void attachColorTexture1D(const GL::Texture&, unsigned);
    void attachColorTexture2D(const GL::Texture&, unsigned);
    inline void attachDepthTexture(const GL::Texture&) const noexcept;
    void attachColorBuffer(const GL::RenderBuffer&, unsigned);
    inline void attachDepthBuffer(const GL::RenderBuffer&) const noexcept;
    void checkStatus() const;
    void attachDrawBuffers() const;

    inline virtual void bind() const noexcept override;
    inline virtual void unbind() const noexcept override;
    inline void bindToRead() const noexcept;
    inline void unbindToRead() const noexcept;
    inline void bindToDraw() const noexcept;
    inline void unbindToDraw() const noexcept;

private:

    static GLint s_maxAttachement;
    static GLint s_maxDraw;
    static bool s_first;

private:

    std::vector< unsigned > m_colorAttachement {};

};

inline void FrameBuffer::blit(int _width, int _height) noexcept
{
    glBlitFramebuffer(0, 0, _width, _height, 0, 0, _width, _height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    assert(glGetError() == GL_NO_ERROR);
}

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

inline void FrameBuffer::bindToRead() const noexcept
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::unbindToRead() const noexcept
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::bindToDraw() const noexcept
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
    assert(glGetError() == GL_NO_ERROR);
}

inline void FrameBuffer::unbindToDraw() const noexcept
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    assert(glGetError() == GL_NO_ERROR);
}

}

