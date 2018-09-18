#pragma once

#include <vector>

#include "GL/IBuffer.hpp"
#include "GL/RenderBuffer.hpp"
#include "GL/Texture.hpp"

namespace GL
{

class FrameBuffer : public IBuffer
{

public:

    FrameBuffer();
    ~FrameBuffer() noexcept;
    FrameBuffer(const FrameBuffer&);
    FrameBuffer(FrameBuffer&&) = delete;
    FrameBuffer& operator=(const FrameBuffer&);
    FrameBuffer& operator=(FrameBuffer&&) = delete;

    void attachColorTexture2D(const GL::Texture&, unsigned) const;
    inline void attachDepthBuffer(const GL::RenderBuffer&) const noexcept;
    void checkStatus() const;

    inline virtual void bind() const noexcept;
    inline virtual void unbind() const noexcept;

};

inline void FrameBuffer::attachDepthBuffer(const GL::RenderBuffer& _buffer) const noexcept
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _buffer.getId());
}

inline void FrameBuffer::bind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

inline void FrameBuffer::unbind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}

