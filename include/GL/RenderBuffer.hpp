#pragma once

#include <vector>

#include "GL/IBuffer.hpp"

namespace GL
{

class RenderBuffer : public IBuffer
{

public:

    RenderBuffer();
    ~RenderBuffer() noexcept;
    RenderBuffer(const RenderBuffer&);
    RenderBuffer(RenderBuffer&&) = delete;
    RenderBuffer& operator=(const RenderBuffer&);
    RenderBuffer& operator=(RenderBuffer&&) = delete;

    inline void setStorage(int, int) const noexcept;

    inline virtual void bind() const noexcept;
    inline virtual void unbind() const noexcept;

};

inline void RenderBuffer::setStorage(int _width, int _height) const noexcept
{
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
}

inline void RenderBuffer::bind() const noexcept
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_id);
}

inline void RenderBuffer::unbind() const noexcept
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

}

