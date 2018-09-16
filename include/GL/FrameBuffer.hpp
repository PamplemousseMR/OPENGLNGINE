#pragma once

#include <vector>

#include "GL/IBuffer.hpp"

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

    inline virtual void bind() const noexcept;
    inline virtual void unbind() const noexcept;

};

inline void FrameBuffer::bind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

inline void FrameBuffer::unbind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}

